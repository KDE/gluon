/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
#include <engine/gameproject.h>
#include <engine/scene.h>

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"
#include "lib/selectionmanager.h"

using namespace GluonCreator;

MainWindow::MainWindow(const QString& fileName) : KXmlGuiWindow()
{
    m_modified = false;

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent(this);
    ObjectManager::instance()->setParent(this);
    HistoryManager::instance()->setParent(this);
    SelectionManager::instance()->setParent(this);

    setupGame();

    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    PluginManager::instance()->setMainWindow(this);
    PluginManager::instance()->loadPlugins();

    setupActions();

    setupGUI();

    if (!fileName.isEmpty())
    {
        openProject(fileName);
    }
    else
    {
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
    if (!fileName.isEmpty() && QFile::exists(fileName))
    {
        GluonEngine::GameProject* project = new GluonEngine::GameProject();
        project->loadFromFile(QUrl(fileName));

        GluonEngine::Game::instance()->setGameProject(project);
        GluonEngine::Game::instance()->initializeAll();
        GluonEngine::Game::instance()->drawAll();

        m_fileName = fileName;

        m_recentFiles->addUrl(KUrl(fileName));
    }
    statusBar()->showMessage(i18n("Project successfully opened"));
    setCaption(i18n("%1 - Gluon Creator").arg(fileName.section('/', -1)));
    HistoryManager::instance()->clear();
}

void MainWindow::saveProject()
{
    saveProject(m_fileName);
}

void MainWindow::saveProject(const QString &fileName)
{
    if (!fileName.isEmpty())
    {
        statusBar()->showMessage(i18n("Saving project..."));
        GluonEngine::Game::instance()->gameProject()->setFilename(QUrl(fileName));
        QDir::setCurrent(KUrl(fileName).directory());
        if (!GluonEngine::Game::instance()->gameProject()->saveToFile())
        {
            KMessageBox::error(this, i18n("Could not save file."));
            return;
        }
        statusBar()->showMessage(i18n("Project successfully saved."));
        setCaption(i18n("%1 - Gluon Creator").arg(fileName.section('/', -1)));
        HistoryManager::instance()->setClean();

        m_recentFiles->addUrl(KUrl(fileName));
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    m_fileName = KFileDialog::getSaveFileName();
    if (!m_fileName.isEmpty()) saveProject();
}

void MainWindow::setupGame()
{
    GluonEngine::GameProject* project = new GluonEngine::GameProject(GluonEngine::Game::instance());
    project->setName(i18n("New Project"));
    setCaption(i18n("%1 - Gluon Creator").arg(i18n("New Project")));
    GluonEngine::Game::instance()->setGameProject(project);

    GluonEngine::Scene* root = ObjectManager::instance()->createNewScene();
    GluonEngine::Game::instance()->setCurrentScene(root);
    project->setEntryPoint(root);

    HistoryManager::instance()->clear();
    //connect(ObjectManager::instance(), SIGNAL(newObject(GluonCore::GluonObject*)), GluonEngine::Game::instance(), SLOT(drawAll()));
    connect(HistoryManager::instance(), SIGNAL(historyChanged()), SLOT(historyChanged()));
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(newProject()), actionCollection());
    KStandardAction::open(this, SLOT(openProject()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());

    KAction *undo = KStandardAction::undo(HistoryManager::instance(), SLOT(undo()), actionCollection());
    undo->setEnabled(false);
    connect(HistoryManager::instance(), SIGNAL(canUndoChanged(bool)), undo, SLOT(setEnabled(bool)));

    KAction *redo = KStandardAction::redo(HistoryManager::instance(), SLOT(redo()), actionCollection());
    redo->setEnabled(false);
    connect(HistoryManager::instance(), SIGNAL(canRedoChanged(bool)), redo, SLOT(setEnabled(bool)));

    connect(HistoryManager::instance(), SIGNAL(cleanChanged(bool)), SLOT(cleanChanged(bool)));

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
}

void MainWindow::showPreferences()
{
    if (KConfigDialog::showDialog("settings"))
    {
        return;
    }
    ConfigDialog *dialog = new ConfigDialog(this, "settings", GluonCreator::Settings::self());
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::playPauseGame(bool checked)
{
    if (checked)
    {
        if (GluonEngine::Game::instance()->isRunning())
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

            //Set the focus to the entire window, so that we do not accidentally trigger actions
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

            GluonEngine::Game::instance()->initializeAll();
            GluonEngine::Game::instance()->drawAll();
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

void MainWindow::historyChanged()
{
    GluonEngine::Game::instance()->drawAll();
    GluonEngine::Game::instance()->currentScene()->savableDirty = true;
    m_modified = true;

    setCaption(i18n("%1 [modified]").arg(m_fileName.isEmpty() ? i18n("New Project") : m_fileName.section('/', -1)));
}

void MainWindow::cleanChanged(bool clean)
{
    if (clean)
    {
        m_modified = false;
        setCaption(i18n("%1").arg(m_fileName.isEmpty() ? i18n("New Project") : m_fileName.section('/', -1)));
    }
}

bool MainWindow::queryClose()
{
    if (m_modified)
    {
        int code = KMessageBox::questionYesNoCancel(this, i18n("The project has been changed. Do you want to save before closing?"), i18n("Save Before Closing?"));

        if (code == KMessageBox::Cancel)
            return false;

        if (code == KMessageBox::No)
            return true;

        saveProject();
        return true;
    }

    return true;
}


