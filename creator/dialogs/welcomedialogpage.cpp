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
    label1 = new QPushButton("&new to creator\n click to start tour");
    label2 = new QPushButton("&get latest updates\n www.gamingfreedom.org");
    label3 = new QPushButton("&Login details");
    QGridLayout *flayout = new QGridLayout;
    QPushButton* push_new= new QPushButton("&new project");
    QPushButton* push_open= new QPushButton("&open project");
    push_new->setFlat(true);
    push_open->setFlat(true);
    label1->setFlat(true);
    label2->setFlat(true);
    label3->setFlat(true);
    QWidget * buttonWidget= new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    dialog_new = new KDialog( this );
    dialog_open = new KDialog( this );
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
    connect(push_new, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(push_open, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), stackedWidget, SLOT(setCurrentIndex(int)));
    if(rp->widget()->isActiveWindow()){ recent_clicked();}
    connect(label2,SIGNAL(clicked()),this, SLOT(webUpdates()));
// connect(this, SIGNAL(accepted()), this, SIGNAL(onAccepted()));

}

WelcomeDialogPage::~WelcomeDialogPage()
{
}

void WelcomeDialogPage::webUpdates()
{
  QWidget *test = new QWidget;
  test->show();
}

void WelcomeDialogPage::recent_clicked()
{
  fileName = rp->selectedItem();
}

void WelcomeDialogPage::new_clicked()
{
    fileName= np->createProject();
    qDebug()<<fileName;
}

void WelcomeDialogPage::projectRequested(QString project){

            fileName = project;
            this->accept();
}

QString WelcomeDialogPage::getfileName() const
{
    return fileName;
}
