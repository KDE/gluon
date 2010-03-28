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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KUrl>

class KRecentFilesAction;
namespace GluonCreator
{
    class Plugin;

    class MainWindow : public KXmlGuiWindow
    {
            Q_OBJECT
        public:
            MainWindow(const QString& fileName = "");
            ~MainWindow();

            virtual bool queryClose();

        public slots:
            void newProject();

            void openProject();
            void openProject(KUrl url);
            void openProject(const QString &fileName);
            void saveProject();
            void saveProject(const QString &fileName);
            void saveProjectAs();
            void showPreferences();

            void playPauseGame(bool checked);
            void stopGame();
            void historyChanged();
            void cleanChanged(bool);

        private:
            void setupActions();
            void setupDocks();
            void setupGame();

            bool m_modified;
            QString m_fileName;
            KRecentFilesAction* m_recentFiles;
    };
}

#endif // MAINWINDOW_H
