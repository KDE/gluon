/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "welcomedialog.h"
#include <core/gluon_global.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/component.h>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KApplication>
#include <KDE/KLineEdit>
#include <KDE/KUrlRequester>
#include <KDE/KMessageBox>
#include <KDE/KSqueezedTextLabel>
#include <QWebView>

using namespace GluonCreator;

WelcomeDialogPage::WelcomeDialogPage()
{
  this->setWindowIcon(QIcon("/home/shreya/gluon/creator/icons/hi32-app-gluon_creator.png"));
  this->setWindowTitle("Welcome to Gluon Creator");
  initializeUi();
  getRecentProjects();
}

void WelcomeDialogPage::getRecentProjects()
{

    const KConfigGroup group = KGlobal::config()->group( "Recent Files" );
    const int entryCount = ( group.entryMap().count() / 2 );

    for( int i = entryCount; i >= 1; --i )
    {
        const QString key = QString( "File%1" ).arg( i );
        const QString path = group.readPathEntry( key, QString() );

        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( KIcon( "document-open-recent" ) );
        QString projectName = KUrl( path ).directory().split( '/' ).last();
        item->setText( QString( "%1\n%2" ).arg( projectName ).arg( path ) );
        item->setData( Qt::UserRole, path );
        recentListWidget->addItem( item );
    }

}

void WelcomeDialogPage::initializeUi()
{
    
    QWidget *firstPageWidget = new QWidget();
    KPageWidget* page_new =  new KPageWidget;
    KPageWidget* page_open =  new KPageWidget;
    np= new NewProjectDialogPage;
    op= new OpenProjectDialogPage;
    newLabel =  new QLabel("New Project");
    recentLabel =  new QLabel("Recent Projects");
    label1 = new QPushButton("&New to creator ?\n Click to start tour");
    label2 = new QPushButton("&Get latest updates\n www.gamingfreedom.org");
    label3 = new QPushButton("&Login details");
    download =  new QPushButton("&Download games");
    QVBoxLayout *flayout = new QVBoxLayout;
    QHBoxLayout *top1 =  new QHBoxLayout;
    QHBoxLayout *top =  new QHBoxLayout;
    QHBoxLayout *mid =  new QHBoxLayout;
    QHBoxLayout *bottom =  new QHBoxLayout;
    QPushButton* pushOpen= new QPushButton("&Open project");
    QWidget * topWidget1= new QWidget;
    QWidget * topWidget= new QWidget;
    QWidget * midWidget= new QWidget;
    QWidget * bottomWidget= new QWidget;
    dialogNew = new KDialog( this );
    dialogOpen = new KDialog( this );
    mapper= new QSignalMapper;
    stackedWidget = new QStackedWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    recentListWidget =  new QListWidget(this);
    newListWidget =  new QListWidget(this);
    QListWidgetItem* newItem = new QListWidgetItem;
    
    newItem->setIcon( KIcon( "document-open-new" ) );
    newItem->setText( "Open Project" );
    newListWidget->addItem(newItem);
    pushOpen->setFlat(true);
    label1->setFlat(true);
    label2->setFlat(true);
    label3->setFlat(true);
    download->setFlat(true);
    page_new->addPage(np);
    page_open ->addPage(op);
    top1->addWidget(newLabel);
    top1->addWidget(recentLabel);
    top->addWidget(newListWidget);
    top->addWidget(recentListWidget);
    mid->addWidget(download);
    mid->addWidget(pushOpen);
    bottom->addWidget(label1);
    bottom->addWidget(label2);
    bottom->addWidget(label3);
    topWidget1->setLayout(top1);
    topWidget->setLayout(top);
    midWidget->setLayout(mid);
    bottomWidget->setLayout(bottom);
    flayout->addWidget(topWidget1);
    flayout->	addWidget(topWidget);
    flayout->addWidget(midWidget);
    flayout->addWidget(bottomWidget);
    firstPageWidget->setLayout(flayout);
    dialogNew->setMainWidget(page_new);
    dialogOpen->setMainWidget(page_open);
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(dialogNew);
    stackedWidget->addWidget(dialogOpen);
    layout->addWidget(stackedWidget,0,0);
    setLayout(layout);
    mapper->setMapping(newListWidget, 1);
    mapper->setMapping(pushOpen, 2);
 
    connect(dialogNew, SIGNAL(okClicked()), this, SLOT(newClicked()));
    connect(dialogNew, SIGNAL(cancelClicked()), this, SLOT(cancelClicked()));
    connect(dialogOpen, SIGNAL(cancelClicked()), this, SLOT(cancelClicked()));
    connect(newListWidget, SIGNAL(doubleClicked(QModelIndex)), mapper, SLOT(map()));
    connect(pushOpen, SIGNAL(clicked()), mapper, SLOT(map()));
    connect( recentListWidget, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(projectDoubleClicked(QModelIndex)) );
    connect(mapper, SIGNAL(mapped(int)), stackedWidget, SLOT(setCurrentIndex(int)));
    connect( this, SIGNAL(projectRequested(QString)),SLOT(ProjectRequested(QString)) );
    connect( op, SIGNAL(projectRequested(QString)),SLOT(ProjectRequested(QString)) );
    connect(label2,SIGNAL(clicked()),this, SLOT(webUpdates()));
  
}
void WelcomeDialogPage::cancelClicked()
{
  stackedWidget->setCurrentIndex(0);
}

WelcomeDialogPage::~WelcomeDialogPage()
{
}

void WelcomeDialogPage::projectDoubleClicked( const QModelIndex& index )
{
   QListWidgetItem* item = static_cast<QListWidgetItem*>( index.internalPointer() );
    if( item )
      emit projectRequested( item->data( Qt::UserRole ).toString() );
}
        
void WelcomeDialogPage::webUpdates()
{
  QWebView *test = new QWebView();
  test->load(QUrl("http://www.gamingfreedom.org"));
  test->show();
}

void WelcomeDialogPage::newClicked()
{
    fileName= np->createProject();
}

void WelcomeDialogPage::ProjectRequested(QString project)
{
  fileName = project;	
  this->accept();
  
}

QString WelcomeDialogPage::getfileName() const
{
    return fileName;
}
