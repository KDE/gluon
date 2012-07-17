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
#include <kconfiggroup.h>
#include <KDE/KColorScheme>
#include <KDE/KDialog>
#include <QtGui>
#include "newprojectdialogpage.h"
#include "openprojectdialogpage.h"

namespace GluonCreator
{

    class WelcomeDialogPage : public QDialog
    {
    Q_OBJECT  
    public:
            WelcomeDialogPage();
            ~WelcomeDialogPage();
	    QStackedWidget *stackedWidget;
	    
	    void getRecentProjects();
	    QString getfileName() const;
            QPushButton *label1,*label2, *label3, *download;
	    QLabel *newLabel,*recentLabel;
	    KDialog *dialogNew;
	    
    public slots:
            void ProjectRequested(QString);
	    void projectDoubleClicked( const QModelIndex& index );
	    void newClicked();
	    void webUpdates();
	    void cancelClicked();
 	    
    signals:
	    void onNew();
	    void clicked();
	    void loadProj();
	    void projectRequested( const QString& url );
	    
           
        private:

            void initializeUi();
	    QWidget* widget;
	    QPixmap *image;
	    QLabel *imageLabel;
	    KDialog *dialogOpen;
	    QString fileName;
	    OpenProjectDialogPage *op;
	    NewProjectDialogPage *np;
            QSignalMapper *mapper;
            QListWidget *recentListWidget;
            QListWidget *newListWidget;
            QHBoxLayout* hlayout;
            QGridLayout* grid;
    };
}

#endif // GLUON_CREATOR_WELCOMEDIALOGPAGE_H
