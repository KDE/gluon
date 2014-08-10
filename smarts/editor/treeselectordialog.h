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

#ifndef TREESELECTORDIALOG_H
#define TREESELECTORDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtCore/QStringListModel>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

#include "bteditor.h"
#include "bttreemodel.h"

class bteditor;

class TreeSelectorDialog : public QDialog
{
        Q_OBJECT
    public:
        TreeSelectorDialog( bteditor* bte );
        ~TreeSelectorDialog();
        void updateModel( QList<btTreeModel*> behaviortrees );
        void updateModel( btTreeModel* behaviortree );
        void setupActions();

    public Q_SLOTS:
        void chooseTree();

    private:
        QVBoxLayout*        mainLayout;
        QHBoxLayout*        buttonLayout;
        QListView*          treelist;
        QPushButton*        cancel_button;
        QPushButton*        ok_button;
        QStringListModel*   model;
        QStringList*        list;
        bteditor*           bte;
};

#endif // TREESELECTORDIALOG_H
