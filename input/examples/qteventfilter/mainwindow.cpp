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

#include "mainwindow.h"

MainWindow::MainWindow( QMainWindow* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags )
    , m_textEdit( 0 )
{
    setupUi();

    createActions();
    createMenus();
    createStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeEvent( QEvent* event )
{
    QMainWindow::changeEvent( event );
    switch( event->type() )
    {
        case QEvent::LanguageChange:
            retranslateUi();
            break;
        default:
            break;
    }
}

void MainWindow::setupUi()
{
    if( objectName().isEmpty() )
        setObjectName( QString::fromUtf8( "MainWindow" ) );

    centralWidget = new QWidget( this );
    centralWidget->setObjectName( QString::fromUtf8( "centralWidget" ) );

    mainLayout = new QGridLayout( centralWidget );
    mainLayout->setObjectName( QString::fromUtf8( "mainLayout" ) );

    m_textEdit = new QTextEdit();
    m_textEdit->setObjectName( QString::fromUtf8( "textEdit" ) );
    m_textEdit->setReadOnly( true );

    mainLayout->addWidget( m_textEdit, 0, 0 );
    mainLayout->setRowStretch( 0, 5 );
    setLayout( mainLayout );

    setCentralWidget( centralWidget );

    menuBar = new QMenuBar( this );
    menuBar->setObjectName( QString::fromUtf8( "menuBar" ) );
    menuBar->setGeometry( QRect( 0, 0, 1290, 20 ) );
    setMenuBar( menuBar );

    statusBar = new QStatusBar( this );
    statusBar->setObjectName( QString::fromUtf8( "statusBar" ) );
    setStatusBar( statusBar );

    setWindowTitle( "Gluon Tutorial 5" );
    setWindowIcon( QIcon( ":/images/icon.bmp" ) );
    setWindowIconText( "Gluon Tutorial 5 application logo" );

    retranslateUi();

    GluonInput::InputManager::instance()->setFilteredObject(m_textEdit);
    return;
}

void MainWindow::retranslateUi()
{
    setWindowTitle( QApplication::translate( "mainwindow", "mainwindow", 0,
                    QApplication::UnicodeUTF8 ) );
    return;
}

void MainWindow::createActions()
{
    // File related actions
    quitAct = new QAction( QIcon( ":/images/quit.png" ), tr( "&Quit" ), this );
    quitAct->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_Q ) );
    quitAct->setStatusTip( tr( "Exit the application" ) );
    connect( quitAct, SIGNAL( triggered() ), this, SLOT( close() ) );

    // Help related actions
    aboutAct = new QAction( tr( "&About" ), this );
    aboutAct->setStatusTip( tr( "Show the Gluon Tutorial 4 Application About box" ) );
    connect( aboutAct, SIGNAL( triggered() ), this, SLOT( mAbout() ) );

    aboutQtAct = new QAction( tr( "About &Qt" ), this );
    aboutQtAct->setStatusTip( tr( "Show the Qt library's About box" ) );
    connect( aboutQtAct, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
}

void MainWindow::createMenus()
{
    // File related menu
    fileMenu = menuBar->addMenu( tr( "&File" ) );
    fileMenu->addAction( quitAct );

    menuBar->addSeparator();

    // Help related menu
    helpMenu = menuBar->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAct );
    helpMenu->addAction( aboutQtAct );
}

void MainWindow::createStatusBar()
{
    statusBar->showMessage( tr( "Ready" ) );
}

void MainWindow::mAbout()
{
    QMessageBox::about( this, tr( "<b>Gluon Tutorial 5 test and example application</b>" ), \
                        tr( "This is a trial application showing the capability "
                            "of the\n Gluon input subsystem." ) );
}

QTextEdit* MainWindow::textEdit()
{
    return m_textEdit;
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    QApplication::instance()->exit( 0 );
}

#include "mainwindow.moc"
