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

#include "propertywidget.h"
#include "gameobjecttreemodel.h"
#include "qobjecttreemodel.h"
#include <klocalizedstring.h>
#include <qlistview.h>
#include <gluon/kgl/kglview.h>


MainWindow::MainWindow() : KXmlGuiWindow()
    , m_propertyWidget(0)
{
    //m_qObjectTree = new QTreeView();
    //m_gameObjectTree = new QTreeView();
    
    QWidget* main = new QWidget(this);
    main->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    main->setFixedSize(QSize(1,1));
    //main->addTab(new QWidget(main), i18n("Preview"));
    //main->addTab(new QWidget(main), i18n("Edit"));
    //QVBoxLayout* layout = new QVBoxLayout;

    //layout->addWidget(m_qObjectTree);
    //layout->addWidget(m_gameObjectTree);

    //main->setLayout(layout);

    setCentralWidget(main);

    setDockNestingEnabled(true);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

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
    QString filename = KFileDialog::getOpenFileName();
    if(filename != "")
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        
        QString data = file.readAll();

        QList<Gluon::GluonObject*> objects = Gluon::GDLHandler::instance()->parseGDL(data, this);
        if(objects.isEmpty())
        {
            // Tell the user this is not proper GDL and then break out
            return;
        }
        
        disconnect(this, SLOT(gameObjectActivated(QItemSelection,QItemSelection)));
        
        Gluon::GluonObject* object = objects.at(0);
        
        QObjectTreeModel *qtree = new QObjectTreeModel(object, m_qObjectTree);
        m_qObjectTree->setModel(qtree);

        GameObjectTreeModel *gtree = new GameObjectTreeModel(qobject_cast<Gluon::GameObject*>(object), m_gameObjectTree);
        m_gameObjectTree->setModel(gtree);
        m_gameObjectTree->setSelectionModel(new QItemSelectionModel(gtree));
        
        connect( m_gameObjectTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(gameObjectActivated(QItemSelection,QItemSelection)) );
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
    delete m_propertyWidget;
    m_propertyWidget = new Gluon::Creator::PropertyWidget(this);
    m_propertyWidgetScrollarea->setWidget(m_propertyWidget);
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
    //Create Scene Dock
    QDockWidget* sceneDock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, sceneDock, Qt::Vertical);
    sceneDock->setWindowTitle(i18n("Scene"));
    sceneDock->setObjectName("sceneDock");
    //sceneDock->setAllowedAreas(Qt::TopDockWidgetArea);
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
    //projectDock->setAllowedAreas(Qt::TopDockWidgetArea);
    m_qObjectTree = new QTreeView(projectDock);
    projectDock->setWidget(m_qObjectTree);
    layout()->setAlignment(projectDock, Qt::AlignLeft);
    //tabifyDockWidget(sceneDock, projectDock);

    QDockWidget* gameDock = new QDockWidget(i18n("Preview"), this);
    gameDock->setObjectName("gameDock");
    addDockWidget(Qt::TopDockWidgetArea, gameDock, Qt::Horizontal);
    gameDock->setWidget(new KGLView(gameDock));
    gameDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->setAlignment(gameDock, Qt::AlignTop);
    
    QDockWidget* editDock = new QDockWidget(i18n("Edit"), this);
    editDock->setObjectName("editDock");
    addDockWidget(Qt::TopDockWidgetArea, editDock, Qt::Horizontal);
    editDock->setWidget(new KGLView(editDock));
    editDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->setAlignment(editDock, Qt::AlignTop);

    tabifyDockWidget(gameDock, editDock);

    QDockWidget* messageDock = new QDockWidget(this);
    addDockWidget(Qt::TopDockWidgetArea, messageDock, Qt::Vertical);
    messageDock->setWindowTitle(i18n("Messages"));
    messageDock->setObjectName("messageDock");
    messageDock->setAllowedAreas(Qt::TopDockWidgetArea);
    messageDock->setWidget(new QTextEdit(messageDock));
    layout()->setAlignment(messageDock, Qt::AlignBottom);

    QDockWidget* propertiesDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, propertiesDock); //, Qt::Horizontal);
    propertiesDock->setWindowTitle(i18n("Properties"));
    propertiesDock->setObjectName("propertiesDock");
    propertiesDock->setAllowedAreas(Qt::TopDockWidgetArea);
    m_propertyWidgetScrollarea = new QScrollArea(propertiesDock);
    propertiesDock->setWidget(m_propertyWidgetScrollarea);
    layout()->setAlignment(propertiesDock, Qt::AlignRight);
    
    QDockWidget* componentDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, componentDock); //, Qt::Vertical);
    componentDock->setWindowTitle(i18n("Components"));
    componentDock->setObjectName("compoentDock");
    componentDock->setAllowedAreas(Qt::TopDockWidgetArea);
    //messageDock->setWidget(new QTextEdit(comDock));*/
    //this->
    //this->layout()->

    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::North);
    
}
