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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

class QTreeView;
class QTextEdit;
class QScrollArea;
class QItemSelection;

namespace Gluon
{
    class GluonObject;

    namespace Creator
    {
        class Plugin;
        class PropertyWidget;
 
        class MainWindow : public KXmlGuiWindow
        {
            Q_OBJECT
            public:
                MainWindow();
                ~MainWindow();
            public slots:
                void newProject();
                void openProject();
                void openProject(const QString &fileName);
                void saveProject();
                void saveProjectAs();
                void gameObjectActivated(const QItemSelection & index, const QItemSelection & deselected);
                void newMessage(const QString & string);
                void loadPlugin(Plugin*);

            private:
                void showPropertiesFor(Gluon::GluonObject * showFor);

                void setupActions();
                void setupDocks();

                QTreeView *m_qObjectTree;
                QTreeView *m_gameObjectTree;
                QScrollArea * m_propertyWidgetScrollarea;
                PropertyWidget * m_propertyWidget;
                QTextEdit * m_messageDock;
        };
    }
}

#endif // MAINWINDOW_H
