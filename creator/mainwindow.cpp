/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "mainwindow.h"

#include <KFileDialog>
#include <KStandardAction>
#include <KActionCollection>
#include <KAction>
#include <KDebug>
#include <KStatusBar>
#include <KMessageBox>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KPluginSelector>
#include <KRun>
#include <KRecentFilesAction>

#include <engine/game.h>
#include <core/gameproject.h>

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"
#include <engine/scene.h>

using namespace GluonCreator;

MainWindow::MainWindow(const QString& fileName) : KXmlGuiWindow()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent(this);
    ObjectManager::instance()->setParent(this);

    setupGame();

    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    PluginManager::instance()->setMainWindow(this);
    PluginManager::instance()->loadPlugins();

    setupActions();

    setupGUI();

    if(!fileName.isEmpty()) {
        openProject(fileName);
    }
    else {
        //Show new project dialog.
    }
}

MainWindow::~MainWindow()
{
    m_recentFiles->saveEntries(KGlobal::config()->group("Recent Files"));
    GluonEngine::Game::instance()->stopGame();
}

void MainWindow::newProject()
{
    KRun::run("gluoncreator", KUrl::List(), this);
}

void MainWindow::openProject()
{
    QString fileName = KFileDialog::getOpenFileName();
    openProject(fileName);
}

void MainWindow::openProject(KUrl url)
{
    openProject(url.path());
}

void MainWindow::openProject(const QString &fileName)
{
    statusBar()->showMessage(i18n("Opening project..."));
    if(!fileName.isEmpty()) {
        GluonCore::GameProject* project = new GluonCore::GameProject();
        project->loadFromFile(QUrl(fileName));

        GluonEngine::Game::instance()->setGameProject(project);
        GluonEngine::Game::instance()->currentScene()->startAll();

        m_fileName = fileName;

        m_recentFiles->addUrl(KUrl(fileName));
    }
    statusBar()->showMessage(i18n("Project successfully opened"));
    setCaption(i18n("%1 - Gluon Creator").arg(fileName.section('/', -1)));
}

void MainWindow::saveProject()
{
    saveProject(m_fileName);
}

void MainWindow::saveProject(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        statusBar()->showMessage(i18n("Saving project..."));
        GluonEngine::Game::instance()->gameProject()->setFilename(QUrl(fileName));
        QDir::setCurrent(KUrl(fileName).directory());
        if(!GluonEngine::Game::instance()->gameProject()->saveToFile())
        {
            KMessageBox::error(this, i18n("Could not save file."));
            return;
        }
        statusBar()->showMessage(i18n("Project successfully saved."));
        setCaption(i18n("%1 - Gluon Creator").arg(fileName.section('/', -1)));
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    m_fileName = KFileDialog::getSaveFileName();
    if(!m_fileName.isEmpty()) saveProject();
}

void MainWindow::setupGame()
{
    GluonCore::GameProject* project = new GluonCore::GameProject(GluonEngine::Game::instance());
    project->setName(i18n("New Project"));
    GluonEngine::Game::instance()->setGameProject(project);

    GluonEngine::Scene* root = ObjectManager::instance()->createNewScene();
    GluonEngine::Game::instance()->setCurrentScene(root);

    connect(ObjectManager::instance(), SIGNAL(newObject(GluonCore::GluonObject*)), GluonEngine::Game::instance(), SLOT(updateAll()));
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(newProject()), actionCollection());
    m_recentFiles = KStandardAction::openRecent(this, SLOT(openProject(KUrl)), actionCollection());
    m_recentFiles->loadEntries(KGlobal::config()->group("Recent Files"));

    KAction* newObject = new KAction(KIcon("document-new"), i18n("New Object"), actionCollection());
    actionCollection()->addAction("newObject", newObject);
    connect(newObject, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewGameObject()));

    KAction* newScene = new KAction(KIcon("document-new"), i18n("New Scene"), actionCollection());
    actionCollection()->addAction("newScene", newScene);
    connect(newScene, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewScene()));

    KAction* play = new KAction(KIcon("media-playback-start"), i18n("Play Game"), actionCollection());
    actionCollection()->addAction("playPauseGame", play);
    play->setCheckable(true);
    connect(play, SIGNAL(triggered(bool)), SLOT(playPauseGame(bool)));

    /*KAction* pause = new KAction(KIcon("media-playback-pause"), i18n("Pause Game"), actionCollection());
    actionCollection()->addAction("pauseGame", pause);
    pause->setCheckable(true);
    pause->setEnabled(false);
    connect(pause, SIGNAL(triggered(bool)), GluonEngine::Game::instance(), SLOT(setPause(bool)));*/

    KAction* stop = new KAction(KIcon("media-playback-stop"), i18n("Stop Game"), actionCollection());
    actionCollection()->addAction("stopGame", stop);
    stop->setEnabled(false);
    connect(stop, SIGNAL(triggered(bool)), SLOT(stopGame()));

    KStandardAction::open(this, SLOT(openProject()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());
}

void MainWindow::showPreferences()
{
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }
    ConfigDialog *dialog = new ConfigDialog(this, "settings", GluonCreator::Settings::self());
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

void MainWindow::playPauseGame(bool checked)
{
    if(checked)
    {
        if(GluonEngine::Game::instance()->isRunning())
        {
            actionCollection()->action("playPauseGame")->setIcon(KIcon("media-playback-pause"));
            actionCollection()->action("playPauseGame")->setText(i18n("Pause Game"));
            GluonEngine::Game::instance()->setPause(false);
        }
        else
        {
            actionCollection()->action("playPauseGame")->setIcon(KIcon("media-playback-pause"));
            actionCollection()->action("playPauseGame")->setText(i18n("Pause Game"));
            actionCollection()->action("stopGame")->setEnabled(true);
            QWidget* oldFocus = focusWidget();
            setFocus();

            //Start the game loop
            //Note that this starts an infinite loop in Game
            GluonEngine::Game::instance()->runGame();

            //This happens after we exit the game loop
            actionCollection()->action("playPauseGame")->setEnabled(true);
            actionCollection()->action("playPauseGame")->setIcon(KIcon("media-playback-start"));
            actionCollection()->action("playPauseGame")->setText(i18n("Play Game"));
            actionCollection()->action("playPauseGame")->setChecked(false);
            actionCollection()->action("stopGame")->setEnabled(false);

            GluonEngine::Game::instance()->currentScene()->startAll();

            oldFocus->setFocus();
        }
    }
    else
    {
        actionCollection()->action("playPauseGame")->setIcon(KIcon("media-playback-start"));
        actionCollection()->action("playPauseGame")->setText(i18n("Play Game"));
        GluonEngine::Game::instance()->setPause(true);
    }
}

void MainWindow::stopGame()
{
    GluonEngine::Game::instance()->stopGame();
}

