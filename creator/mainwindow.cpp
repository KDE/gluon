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
#include <QMenuBar>
#include <QScrollArea>
#include <QDockWidget>
#include <KFileDialog>
#include <KStandardAction>
#include <KActionCollection>
#include <KAction>
#include <KDebug>
#include <KApplication>

#include <gluon/gdlhandler.h>
#include <gluon/gluonobject.h>
#include <gluon/gameobject.h>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTreeView>
#include <QDebug>
#include <QVariant>

//#include "widgets/propertywidget.h"
//##include "models/scenemodel.h"
//#include "models/qobjecttreemodel.h"
#include <klocalizedstring.h>
#include <qlistview.h>
//#include <gluon/kgl/kglview.h>

#include <game.h>
#include <gameproject.h>

#include "lib/plugin.h"
#include "lib/pluginloader.h"

#include <QMessageBox>
#include <KStatusBar>
#include <KMessageBox>

using namespace Gluon::Creator;

MainWindow::MainWindow() : KXmlGuiWindow()
    , m_propertyWidget(0)
{
    Gluon::GluonObjectFactory::instance()->loadPlugins();

    setupGame();

    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    m_uid = 0;
    m_sceneId = 0;

    connect(PluginLoader::instance(), SIGNAL(pluginLoaded(Plugin*)), SLOT(loadPlugin(Plugin*)));
    PluginLoader::instance()->loadAllPlugins();

    setupActions();

    setupGUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::newProject()
{

}

void MainWindow::openProject()
{
    QString fileName = KFileDialog::getOpenFileName();
    openProject(fileName);
}

void MainWindow::openProject(const QString &fileName)
{
    statusBar()->showMessage(i18n("Opening project..."));
    if(!fileName.isEmpty()) {
        Gluon::GameProject* project = new Gluon::GameProject();
        project->loadFromFile(QUrl(fileName));

        Gluon::Game::instance()->setGameProject(project);
    }
    statusBar()->showMessage(i18n("Project successfully opened"));
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
        Gluon::Game::instance()->gameProject()->setFilename(QUrl(fileName));
        if(!Gluon::Game::instance()->gameProject()->saveToFile())
        {
            KMessageBox::error(this, i18n("Could not save file."));
            return;
        }
        statusBar()->showMessage(i18n("Project successfully saved."));
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

void MainWindow::gameObjectActivated(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected)
    Q_UNUSED(deselected)
    //Gluon::GluonObject* selectedObject = static_cast<Gluon::GluonObject*>(m_gameObjectTree->selectionModel()->currentIndex().internalPointer());
//    showPropertiesFor(selectedObject);
}

void MainWindow::showPropertiesFor(Gluon::GluonObject * showFor)
{
  //  m_propertyWidget->clear();
//    m_propertyWidget->setObject(showFor);
}


void MainWindow::setupGame()
{
    Gluon::GameProject* project = new Gluon::GameProject(Gluon::Game::instance());
    project->setName(i18n("New Project"));
    Gluon::GameObject* root = new Gluon::GameObject(project);
    root->setName(i18n("New Scene"));
    project->addChild(root);

    Gluon::Game::instance()->setGameProject(project);
    Gluon::Game::instance()->setCurrentScene(root);
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(newProject()), actionCollection());

    KAction* newObject = new KAction(KIcon("document-new"), i18n("New Object"), actionCollection());
    actionCollection()->addAction("newObject", newObject);
    connect(newObject, SIGNAL(triggered(bool)), SLOT(newObject()));

    KAction* newScene = new KAction(KIcon("document-new"), i18n("New Scene"), actionCollection());
    actionCollection()->addAction("newScene", newScene);
    connect(newObject, SIGNAL(triggered(bool)), SLOT(newScene()));

    KStandardAction::open(this, SLOT(openProject()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
}

void MainWindow::setupDocks()
{

}


void MainWindow::newMessage(const QString &string)
{
    //m_messageDock->append(string);
}

void MainWindow::loadPlugin(Plugin* plugin)
{
    plugin->initialize(this);
}

void MainWindow::newObject()
{
    Gluon::GameObject * newObject = new Gluon::GameObject();
    newObject->setName(QString("New Object %1").arg(m_uid++));
    Gluon::Game::instance()->currentScene()->addChild(newObject);

}

void MainWindow::newScene()
{
    Gluon::GameObject* newObject = new Gluon::GameObject();
    newObject->setName(QString("New Scene %1").arg(m_sceneId++));
    Gluon::Game::instance()->gameProject()->addChild(newObject);
}

