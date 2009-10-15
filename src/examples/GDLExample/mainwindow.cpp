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

#include "gameobjecttreemodel.h"
#include "qobjecttreemodel.h"
#include <klocalizedstring.h>
#include <qlistview.h>


MainWindow::MainWindow() : KXmlGuiWindow()
{
    //m_qObjectTree = new QTreeView();
    //m_gameObjectTree = new QTreeView();
    
    QTabWidget* main = new QTabWidget(this);
    main->addTab(new QWidget(main), i18n("Preview"));
    main->addTab(new QWidget(main), i18n("Edit"));
    //QVBoxLayout* layout = new QVBoxLayout;

    //layout->addWidget(m_qObjectTree);
    //layout->addWidget(m_gameObjectTree);

    //main->setLayout(layout);

    setCentralWidget(main);

    setupActions();
    setupDocks();

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
    QString filename = KFileDialog::getOpenFileName();
    if(filename != "")
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        
        QString data = file.readAll();

        QList<Gluon::GluonObject*> objects = Gluon::GDLHandler::instance()->parseGDL(data, this);

        Gluon::GluonObject* object = objects.at(0);
        
        QObjectTreeModel *qtree = new QObjectTreeModel(object, m_qObjectTree);
        m_qObjectTree->setModel(qtree);

        GameObjectTreeModel *gtree = new GameObjectTreeModel(qobject_cast<Gluon::GameObject*>(object), m_gameObjectTree);
        m_gameObjectTree->setModel(gtree);
    }
}

void MainWindow::saveProject()
{

}

void MainWindow::saveProjectAs()
{

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
    //Create Scene Dock
    QDockWidget* sceneDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, sceneDock);
    sceneDock->setWindowTitle(i18n("Scene"));
    sceneDock->setObjectName("sceneDock");
    m_gameObjectTree = new QTreeView(sceneDock);
    sceneDock->setWidget(m_gameObjectTree);

    //Create scene dock actions
    KAction* showSceneDockAction = new KAction(i18n("Show Scene Dock"), this);
    actionCollection()->addAction("showSceneDockAction", showSceneDockAction);
    showSceneDockAction->setCheckable(true);
    connect(showSceneDockAction, SIGNAL(toggled(bool)), sceneDock, SLOT(setVisible(bool)));
    //showSceneDockActions

    QDockWidget* projectDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, projectDock);
    projectDock->setWindowTitle(i18n("Project"));
    projectDock->setObjectName("projectDock");
    m_qObjectTree = new QTreeView(projectDock);
    projectDock->setWidget(m_qObjectTree);
    
    QDockWidget* propertiesDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, propertiesDock);
    propertiesDock->setWindowTitle(i18n("Properties"));
    propertiesDock->setObjectName("propertiesDock");
    propertiesDock->setWidget(new QListView(propertiesDock));
    
    QDockWidget* messageDock = new QDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, messageDock);
    messageDock->setWindowTitle(i18n("Messages"));
    messageDock->setObjectName("messageDock");
    messageDock->setWidget(new QTextEdit(messageDock));
    
}
