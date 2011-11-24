/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTNODEEDITWIDGET_H
#define GLUON_SMARTS_BTNODEEDITWIDGET_H

#include <QtGui/QWidget>

class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTableView;
class QPushButton;

class btnodemodel;
class btNodeTypesModelNode;
class btQListDeletgate;
class btTreeModel;

class btNodeEditWidget : public QWidget
{
        Q_OBJECT

    public:
        btNodeEditWidget( QWidget* parent );
        ~btNodeEditWidget();

        void setModel( btnodemodel* btmodel );
        void setSelectedNode( btNodeTypesModelNode* selectedNode );
        void connectSignals();
        void disconnectSignals( btTreeModel* currentBehaviorTree );

    private:
        QVBoxLayout*     mainLayout;
        QHBoxLayout*     buttonLayout;
        QGridLayout*     editLayout;
        QLabel*          name;
        QLabel*          classname;
        QLabel*          description;
        QLabel*          properties;
        QLineEdit*       nameedit;
        QLineEdit*       classnameedit;
        QLineEdit*       descriptionedit;
        QTableView*      propertyList;
        QPushButton*     remove_button;
        QPushButton*     add_button;
        btnodemodel*     model;
        btNodeTypesModelNode* m_selectedNode;
        btQListDeletgate* delegate;

    public Q_SLOTS:
        void nameEdited( QString name );
        void classnameEdited( QString classname );
        void descriptionEdited( QString description );
        void add_button_clicked();
        void remove_button_clicked();

};

#endif // GLUON_SMARTS_BTNODEEDITWIDGET_H
