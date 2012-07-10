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

#include "welcomedialogpage.h"

#include <core/gluon_global.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/component.h>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <QVBoxLayout>
#include <KDE/KApplication>
#include <KDE/KLineEdit>
#include <KDE/KUrlRequester>
#include <KDE/KMessageBox>
#include <KDE/KSqueezedTextLabel>
#include <QWidget>
#include <QComboBox>
#include <QtGui/QLabel>
#include <QString>
#include <QDebug>

#include <kpagewidget.h>

class QLabel;
using namespace GluonCreator;

WelcomeDialogPage::WelcomeDialogPage()
{
  getUi();
}

void WelcomeDialogPage::getUi()

{
    QWidget *firstPageWidget = new QWidget();
    KPageWidget* page_recent =  new KPageWidget;
    KPageWidget* page_new =  new KPageWidget;
    KPageWidget* page_open =  new KPageWidget;
    np= new NewProjectDialogPage;
    rp = new RecentProjectsDialogPage; 
    op= new OpenProjectDialogPage;
    label1 = new QLabel("new to creator\n click to start tour");
    label2 = new QLabel("get latest updates\n www.gamingfreedom.org");
    label3 = new QLabel("Login details");
    QGridLayout *flayout = new QGridLayout;
    QPushButton* push_new= new QPushButton("&new project");
    QPushButton* push_open= new QPushButton("&open project");
    QWidget * buttonWidget= new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    KDialog *dialog_new = new KDialog( this );
    KDialog *dialog_open = new KDialog( this );
    mapper= new QSignalMapper;
    stackedWidget = new QStackedWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    
    page_new->addPage(np);
    page_recent->addPage(rp);
    page_open ->addPage(op);
    buttonLayout->addWidget(push_new);
    buttonLayout->addWidget(push_open);
    buttonWidget->setLayout(buttonLayout);
    flayout->addWidget(buttonWidget,0,0);
    flayout->addWidget(page_recent,0,1);
    flayout->addWidget(label1,1,0);
    flayout->addWidget(label2,1,1);
    flayout->addWidget(label3,1,2);
    
    firstPageWidget->setLayout(flayout);
    dialog_new->setMainWidget(page_new);
    dialog_open->setMainWidget(page_open);
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(dialog_new);
    stackedWidget->addWidget(dialog_open);
    
    layout->addWidget(stackedWidget);
    setLayout(layout);
    mapper->setMapping(push_new, 1);
    mapper->setMapping(push_open, 2);
    connect(push_new, SIGNAL(clicked()), this, SLOT(new_clicked()));
    connect(push_open, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), stackedWidget, SLOT(setCurrentIndex(int)));
     
}

WelcomeDialogPage::~WelcomeDialogPage()
{

}

void WelcomeDialogPage::new_clicked()
{
  NewProjectDialogPage* page = static_cast<NewProjectDialogPage*>( q->currentPage() );
                if( page )
  fileName = page->createProject();
  mapper->map();
}

void WelcomeDialogPage::projectRequested(QString project){

            fileName = project;
            this->accept();
}

