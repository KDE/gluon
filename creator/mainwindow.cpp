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

using namespace Gluon::Creator;

MainWindow::MainWindow() : KXmlGuiWindow()
    , m_propertyWidget(0)
{
    setupGame();

    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    m_uid = 0;
    
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
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        
        QString data = file.readAll();

        QList<Gluon::GluonObject*> objects = Gluon::GDLHandler::instance()->parseGDL(data, this);
        if(objects.isEmpty())
        {
            // Tell the user this is not proper GDL and then break out
            //QMessageBox::warning ( this , "Loading Error" , "Layer 8 Problem, RTFM Module" ,
             //                                     "OK"  );
            QMessageBox::warning ( this , "Loading Error" , "not a proper GDL file" ,
                                  "OK"  );
            newMessage( "Project loading faild");
            return;
        }
        
        disconnect(this, SLOT(gameObjectActivated(QItemSelection,QItemSelection)));
        
        //Gluon::GluonObject* object = objects.at(0);
        
//        QObjectTreeModel *qtree = new QObjectTreeModel(object, m_qObjectTree);
  //      m_qObjectTree->setModel(qtree);

        //SceneModel *gtree = new SceneModel(m_gameObjectTree);
        //gtree->setRootGameObject(qobject_cast<Gluon::GameObject*>(object));
        //m_gameObjectTree->setModel(gtree);
        //m_gameObjectTree->setSelectionModel(new QItemSelectionModel(gtree));
        
    //    connect( m_gameObjectTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(gameObjectActivated(QItemSelection,QItemSelection)) );

        newMessage( "Project loaded");
    }
}

void MainWindow::saveProject()
{

}

void MainWindow::saveProjectAs()
{

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

}

