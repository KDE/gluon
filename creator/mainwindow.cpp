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

#include <gluon/gdlhandler.h>
#include <gluon/gluonobject.h>
#include <gluon/gameobject.h>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTreeView>
#include <QDebug>
#include <QVariant>

#include "widgets/propertywidget.h"
//##include "models/scenemodel.h"
#include "models/qobjecttreemodel.h"
#include <klocalizedstring.h>
#include <qlistview.h>
#include <gluon/kgl/kglview.h>

 #include <QMessageBox>

using namespace Gluon::Creator;

MainWindow::MainWindow() : KXmlGuiWindow()
    , m_propertyWidget(0)
{
    setupDocks();
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
        
        Gluon::GluonObject* object = objects.at(0);
        
        QObjectTreeModel *qtree = new QObjectTreeModel(object, m_qObjectTree);
        m_qObjectTree->setModel(qtree);

        //SceneModel *gtree = new SceneModel(m_gameObjectTree);
        //gtree->setRootGameObject(qobject_cast<Gluon::GameObject*>(object));
        //m_gameObjectTree->setModel(gtree);
        //m_gameObjectTree->setSelectionModel(new QItemSelectionModel(gtree));
        
        connect( m_gameObjectTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(gameObjectActivated(QItemSelection,QItemSelection)) );

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
    Gluon::GluonObject* selectedObject = static_cast<Gluon::GluonObject*>(m_gameObjectTree->selectionModel()->currentIndex().internalPointer());
    showPropertiesFor(selectedObject);
}

void MainWindow::showPropertiesFor(Gluon::GluonObject * showFor)
{
    m_propertyWidget->clear();
    m_propertyWidget->setObject(showFor);
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(newProject()), actionCollection());
    KStandardAction::open(this, SLOT(openProject()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
}

void MainWindow::setupDocks()
{
    setDockNestingEnabled(true);
    //Create Scene Dock
    QDockWidget* sceneDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, sceneDock, Qt::Vertical);
    sceneDock->setWindowTitle(i18n("Scene"));
    sceneDock->setObjectName("sceneDock");
    sceneDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_gameObjectTree = new QTreeView(sceneDock);
    sceneDock->setWidget(m_gameObjectTree);
    layout()->setAlignment(sceneDock, Qt::AlignLeft);

    //Create scene dock actions
    KAction* showSceneDockAction = new KAction(i18n("Show Scene Dock"), this);
    actionCollection()->addAction("showSceneDockAction", showSceneDockAction);
    showSceneDockAction->setCheckable(true);
    connect(showSceneDockAction, SIGNAL(toggled(bool)), sceneDock, SLOT(setVisible(bool)));
    //showSceneDockActions

    QDockWidget* projectDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, projectDock, Qt::Vertical);
    projectDock->setWindowTitle(i18n("Project"));
    projectDock->setObjectName("projectDock");
    projectDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_qObjectTree = new QTreeView(projectDock);
    projectDock->setWidget(m_qObjectTree);
    layout()->setAlignment(projectDock, Qt::AlignLeft);

    QDockWidget* componentDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, componentDock); //, Qt::Vertical);
    componentDock->setWindowTitle(i18n("Components"));
    componentDock->setObjectName("componentDock");
    componentDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    tabifyDockWidget(projectDock, componentDock);

    QDockWidget* gameDock = new QDockWidget(i18n("Preview"), this);
    gameDock->setObjectName("gameDock");
    addDockWidget(Qt::LeftDockWidgetArea, gameDock, Qt::Horizontal);
    gameDock->setWidget(new KGLView(gameDock));
    gameDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gameDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layout()->setAlignment(gameDock, Qt::AlignTop);
    
    QDockWidget* editDock = new QDockWidget(i18n("Edit"), this);
    editDock->setObjectName("editDock");
    addDockWidget(Qt::LeftDockWidgetArea, editDock, Qt::Horizontal);
    editDock->setWidget(new KGLView(editDock));
    editDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layout()->setAlignment(editDock, Qt::AlignTop);

    tabifyDockWidget(gameDock, editDock);


    QDockWidget* propertiesDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, propertiesDock); //, Qt::Horizontal);
    propertiesDock->setWindowTitle(i18n("Properties"));
    propertiesDock->setObjectName("propertiesDock");
    propertiesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_propertyWidget = new Gluon::Creator::PropertyWidget(this);
    propertiesDock->setWidget(m_propertyWidget);
    layout()->setAlignment(propertiesDock, Qt::AlignRight);
    

    QDockWidget* messageDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, messageDock, Qt::Vertical);
    messageDock->setWindowTitle(i18n("Messages"));
    messageDock->setObjectName("messageDock");
    messageDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_messageDock = new QTextEdit(messageDock);
    m_messageDock->setReadOnly(true);
    m_messageDock->append(i18n("Logging started"));
    messageDock->setWidget(m_messageDock);
    layout()->setAlignment(messageDock, Qt::AlignBottom);
    
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);

//    setMinimumSize(200, 500);
}


void MainWindow::newMessage(const QString &string)
{
    m_messageDock->append(string);
}
