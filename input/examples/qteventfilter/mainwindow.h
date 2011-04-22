/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include <gluon/input/inputmanager.h>

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QGridLayout>
#include <QAction>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow( QMainWindow* parent = 0,  Qt::WindowFlags flags = 0 );
        virtual ~MainWindow();

        QTextEdit* textEdit();
        virtual void closeEvent( QCloseEvent* event );

    private:
        void setupUi();
        void retranslateUi();

        void createActions();
        void createMenus();
        void createStatusBar();

        void changeEvent( QEvent* event );

    private slots:
        void mAbout();
        void mKeyPressed( int button );
        void mKeyReleased( int button );

    private:
        QWidget* centralWidget;
        QGridLayout* mainLayout;
        QTextEdit* m_textEdit;

        QMenuBar* menuBar;
        QStatusBar* statusBar;

        QAction* quitAct;

        QAction* aboutAct;
        QAction* aboutQtAct;

        QMenu*   fileMenu;
        QMenu*   helpMenu;
};

#endif // MAINWINDOW_H
