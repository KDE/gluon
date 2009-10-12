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


MainWindow::MainWindow() : KXmlGuiWindow()
{
    KStandardAction::open(this, SLOT(openFile(bool)), actionCollection());
    setupGUI();

    m_tree = new QTreeView();
    
    setCentralWidget(m_tree);
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
        GameObjectTreeModel *tree = new GameObjectTreeModel(static_cast<Gluon::GameObject*>(object), m_tree);
        m_tree->setModel(tree);
        m_tree->update();
    }
}
