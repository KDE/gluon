/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtCore/QVariantList>

#include <KFileDialog>
#include <KStandardAction>
#include <KActionCollection>
#include <KAction>
#include <KStatusBar>
#include <KMessageBox>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KPluginSelector>
#include <KRun>
#include <KRecentFilesAction>
#include <KDE/KTabWidget>
#include <KDE/KToolBar>
#include <KDE/KRichTextEdit>

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"
#include "lib/selectionmanager.h"
#include "lib/dockmanager.h"
#include "lib/filemanager.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"
#include <QVBoxLayout>
#include <KParts/PartManager>

using namespace GluonCreator;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate() { viewPart = 0; }
        
        bool modified;
        QString fileName;
        KRecentFilesAction* recentFiles;
        ProjectSelectionDialog *projectDialog;

        KParts::ReadOnlyPart *viewPart;
};

MainWindow::MainWindow(const QString& fileName)
    : KParts::MainWindow(),
      d(new MainWindowPrivate)
{
    d->modified = false;
    
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent(this);
    ObjectManager::instance()->setParent(this);
    HistoryManager::instance()->setParent(this);
    SelectionManager::instance()->setParent(this);
    DockManager::instance()->setParent(this);
    FileManager::instance()->setParent(this);
    DockManager::instance()->setMainWindow(this);

    setDockNestingEnabled(true);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    
    PluginManager::instance()->setMainWindow(this);
    PluginManager::instance()->loadPlugins();

    setupActions();
    setupGUI();
    
    d->projectDialog = new ProjectSelectionDialog(this);
    d->projectDialog->setModal(true);
    connect(d->projectDialog, SIGNAL(okClicked()), SLOT(projectDialogClosed()));
    
    DockManager::instance()->setDocksEnabled(false);
    DockManager::instance()->setDocksLocked(GluonCreator::Settings::lockLayout());

    KTabWidget *tab = new KTabWidget(this);
    tab->setCloseButtonEnabled(true);
    tab->setMovable(true);
    tab->setEnabled(false);

    KService::Ptr viewerService = KService::serviceByDesktopName("gluon_viewer_part");
    if(viewerService)
    {
        d->viewPart = viewerService->createInstance<KParts::ReadOnlyPart>(0, QVariantList() << QString("autoplay=false"));
        if(d->viewPart)
        {
            d->viewPart->widget()->setObjectName("gluon_viewer_part");
            tab->addTab(d->viewPart->widget(), i18nc("View Game Tab", "View"));
        }
    }

    if(!d->viewPart)
    {
        KMessageBox::error(this, "Could not load the Viewer part. Is it installed correctly?");
    }

    tab->addTab(new QWidget(), i18nc("Edit Game Tab", "Edit"));
    setCentralWidget(tab);

    FileManager::instance()->setTabWidget(tab);
    connect(FileManager::instance()->partManager(), SIGNAL(activePartChanged(KParts::Part*)), this, SLOT(createGUI(KParts::Part*)));

    if (!fileName.isEmpty())
    {
        openProject(fileName);
    }
    else
    {
        //Show new project dialog.
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), SLOT(showNewProjectDialog()));
        timer->start();
    }
}

MainWindow::~MainWindow()
{
    d->recentFiles->saveEntries(KGlobal::config()->group("Recent Files"));
    GluonCreator::Settings::setLockLayout(actionCollection()->action("lockLayout")->isChecked());
    GluonCreator::Settings::self()->writeConfig();
    GluonEngine::Game::instance()->stopGame();
}

void MainWindow::openProject(KUrl url)
{
    openProject(url.path());
}

void MainWindow::openProject(const QString &fileName)
{
    statusBar()->showMessage(i18n("Opening project..."));
    if (!fileName.isEmpty() && QFile::exists(fileName) && d->viewPart)
    {
        d->viewPart->openUrl(KUrl(fileName));
        GluonEngine::Game::instance()->initializeAll();
        GluonEngine::Game::instance()->drawAll();

        d->fileName = fileName;

        d->recentFiles->addUrl(KUrl(fileName));

        actionCollection()->action(KStandardAction::name(KStandardAction::Save))->setEnabled(true);
        actionCollection()->action(KStandardAction::name(KStandardAction::SaveAs))->setEnabled(true);
        actionCollection()->action("newObject")->setEnabled(true);
        actionCollection()->action("newScene")->setEnabled(true);
        actionCollection()->action("playPauseGame")->setEnabled(true);
        actionCollection()->action("addAsset")->setEnabled(true);
        actionCollection()->action("chooseEntryPoint")->setEnabled(true);

        DockManager::instance()->setDocksEnabled(true);

        if(centralWidget())
            centralWidget()->setEnabled(true);

        statusBar()->showMessage(i18n("Project successfully opened"));
        setCaption(i18n("%1 - Gluon Creator", fileName.section('/', -1)));
        HistoryManager::instance()->clear();
        connect(HistoryManager::instance(), SIGNAL(historyChanged()), SLOT(historyChanged()));
    }
}

void MainWindow::saveProject()
{
    saveProject(d->fileName);
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
        setCaption(i18n("%1 - Gluon Creator", fileName.section('/', -1)));
        HistoryManager::instance()->setClean();

        d->recentFiles->addUrl(KUrl(fileName));
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    d->fileName = KFileDialog::getSaveFileName(KUrl(), i18n("*.gluon|Gluon Project Files"));
    if (!d->fileName.isEmpty()) saveProject();
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(showNewProjectDialog()), actionCollection());
    KStandardAction::open(this, SLOT(showOpenProjectDialog()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection())->setEnabled(false);
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection())->setEnabled(false);;
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());

    KAction *undo = KStandardAction::undo(HistoryManager::instance(), SLOT(undo()), actionCollection());
    undo->setEnabled(false);
    connect(HistoryManager::instance(), SIGNAL(canUndoChanged(bool)), undo, SLOT(setEnabled(bool)));

    KAction *redo = KStandardAction::redo(HistoryManager::instance(), SLOT(redo()), actionCollection());
    redo->setEnabled(false);
    connect(HistoryManager::instance(), SIGNAL(canRedoChanged(bool)), redo, SLOT(setEnabled(bool)));

    connect(HistoryManager::instance(), SIGNAL(cleanChanged(bool)), SLOT(cleanChanged(bool)));

    d->recentFiles = KStandardAction::openRecent(this, SLOT(openProject(KUrl)), actionCollection());
    d->recentFiles->loadEntries(KGlobal::config()->group("Recent Files"));

    KAction* newObject = new KAction(KIcon("document-new"), i18n("New Object"), actionCollection());
    actionCollection()->addAction("newObject", newObject);
    newObject->setEnabled(false);
    connect(newObject, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewGameObject()));

    KAction* newScene = new KAction(KIcon("document-new"), i18n("New Scene"), actionCollection());
    actionCollection()->addAction("newScene", newScene);
    newScene->setEnabled(false);
    connect(newScene, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewScene()));

    KAction* play = new KAction(KIcon("media-playback-start"), i18n("Play Game"), actionCollection());
    actionCollection()->addAction("playPauseGame", play);
    play->setCheckable(true);
    play->setEnabled(false);
    connect(play, SIGNAL(triggered(bool)), SLOT(playPauseGame(bool)));

    KAction* stop = new KAction(KIcon("media-playback-stop"), i18n("Stop Game"), actionCollection());
    actionCollection()->addAction("stopGame", stop);
    stop->setEnabled(false);
    connect(stop, SIGNAL(triggered(bool)), SLOT(stopGame()));
    
    KAction *addAsset = new KAction(KIcon("document-new"), i18n("Add Assets..."), actionCollection());
    actionCollection()->addAction("addAsset", addAsset);
    addAsset->setEnabled(false);
    connect(addAsset, SIGNAL(triggered(bool)), SLOT(addAsset()));
    
    KAction* chooseEntryPoint = new KAction(KIcon("media-playback-start"), i18n("Set current scene as entry point"), actionCollection());
    actionCollection()->addAction("chooseEntryPoint", chooseEntryPoint);
    chooseEntryPoint->setEnabled(false);
    connect(chooseEntryPoint, SIGNAL(triggered(bool)), SLOT(chooseEntryPoint()));

    KAction *lockLayout = new KAction(KIcon("object-locked"), i18n("Lock layout"), actionCollection());
    actionCollection()->addAction("lockLayout", lockLayout);
    lockLayout->setCheckable(true);
    lockLayout->setChecked(GluonCreator::Settings::lockLayout());
    connect(lockLayout, SIGNAL(triggered(bool)), DockManager::instance(), SLOT(setDocksLocked(bool)));
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
            
            QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
            saveProject();

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
            
            openProject(d->fileName);
            
            DEBUG_BLOCK;
            DEBUG_TEXT(currentSceneName);
            GluonEngine::Game::instance()->setCurrentScene(currentSceneName);
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
    d->modified = true;

    setCaption(i18n("%1 [modified]", d->fileName.isEmpty() ? i18n("New Project") : d->fileName.section('/', -1)));
}

void MainWindow::cleanChanged(bool clean)
{
    if (clean)
    {
        d->modified = false;
        setCaption(i18n("%1", d->fileName.isEmpty() ? i18n("New Project") : d->fileName.section('/', -1)));
    }
}

bool MainWindow::queryClose()
{
    if (d->modified)
    {
        int code = KMessageBox::questionYesNoCancel(this, i18n("The project has been changed. Do you want to save before closing?"), i18n("Save Before Closing?"),
                                                    KStandardGuiItem::save(), KStandardGuiItem::dontSave());

        if (code == KMessageBox::Cancel)
            return false;

        if (code == KMessageBox::No)
            return true;

        saveProject();
        return true;
    }

    return true;
}

void MainWindow::addAsset()
{
    QStringList assets = KFileDialog::getOpenFileNames();
    
    foreach(const QString &asset, assets)
    {
        ObjectManager::instance()->createNewAsset(asset);
    }
}

void MainWindow::chooseEntryPoint()
{
    if(GluonEngine::Game::instance()->gameProject())
    {
        if(GluonEngine::Game::instance()->currentScene())
        {
            GluonEngine::Game::instance()->gameProject()->setEntryPoint(GluonEngine::Game::instance()->currentScene());
        }
    }
}

void GluonCreator::MainWindow::showNewProjectDialog()
{
    d->projectDialog->setPage(ProjectSelectionDialog::PROJECTPAGE_NEW);
    d->projectDialog->show();
}

void GluonCreator::MainWindow::showOpenProjectDialog()
{
    d->projectDialog->setPage(ProjectSelectionDialog::PROJECTPAGE_OPEN);
    d->projectDialog->show();
}

void GluonCreator::MainWindow::projectDialogClosed()
{
    openProject(d->projectDialog->fileName());
    

}
