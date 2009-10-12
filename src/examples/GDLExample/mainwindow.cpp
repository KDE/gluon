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
#include <KFileDialog>
#include <KStandardAction>
#include <KActionCollection>

#include <gluon/gdlhandler.h>
#include <gluon/gluonobject.h>
#include <gluon/gameobject.h>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTreeView>
#include <QDebug>

#include "gameobjecttreemodel.h"
#include "qobjecttreemodel.h"


MainWindow::MainWindow() : KXmlGuiWindow()
{
    KStandardAction::open(this, SLOT(openFile(bool)), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    
    setupGUI();

    m_qObjectTree = new QTreeView();
    m_gameObjectTree = new QTreeView();
    
    QWidget* main = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(m_qObjectTree);
    layout->addWidget(m_gameObjectTree);

    main->setLayout(layout);
    
    setCentralWidget(main);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::openFile(bool )
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
