/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_CREATOR_WELCOMEDIALOGPAGE_H
#define GLUON_CREATOR_WELCOMEDIALOGPAGE_H

#include <KDE/KPageWidgetItem>
#include <KDE/KPageWidget>
#include <KDE/KColorScheme>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <KDE/KDialog>
#include <QMouseEvent>
#include <QLayoutItem>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QSignalMapper>
#include <QtGui>
#include "newprojectdialogpage.h"
#include <dialogs/openprojectdialogpage.h>
#include "recentprojectsdialogpage.h"

class QLabel;
namespace GluonCreator
{

    class WelcomeDialogPage : public QDialog
    {
        public:
            WelcomeDialogPage();
            ~WelcomeDialogPage();
	    QStackedWidget *stackedWidget;
	    void getUi();
	    void recent_clicked();
	    QString getfileName() const;
	    
    signals:
	    void onNew();
	    void clicked();
	    void loadProj();
	    
        public slots:
            void projectRequested(QString);
	    void new_clicked();
	    void webUpdates();
	    
        private:

            QWidget* widget;
	    KDialog *dialog_new;
	    KDialog *dialog_open;
	    QString fileName;
	    RecentProjectsDialogPage* rp;
	    OpenProjectDialogPage *op;
	    NewProjectDialogPage *np;
            QPushButton *label1,*label2, *label3;
            QSignalMapper *mapper;
            QListWidget *listWidget;
            QHBoxLayout* hlayout;
            QGridLayout* grid;
    };
}

#endif // GLUON_CREATOR_WELCOMEDIALOGPAGE_H
