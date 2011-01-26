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

#ifndef ACTIONSDIALOG_H
#define ACTIONSDIALOG_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVariant>
#include <QApplication>
#include <QButtonGroup>
#include <QList>
#include <QAction>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QStringList>
#include <QPushButton>
#include <QSettings>
#include <QScopedPointer>
#include <QDebug>

namespace Ui
{
    class ActionsDialog;
}

class ActionsDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit ActionsDialog( QList<QAction*> actions,
                                QWidget* parent = 0 );
        virtual ~ActionsDialog();

    protected:
        void changeEvent( QEvent* e );

    protected slots:
        void accept();

    private slots:
        void recordAction( int curr_row, int curr_col, int prev_row,
                           int prev_col );
        void validateAction( int row, int col );
        void mSaveShortcuts();
        void buttonBoxClicked( QAbstractButton* optionsDialogPushButton );

    private:
        void setupUi();
        void retranslateUi();
        void setFallbacksEnabled( bool enabled );

        QString oldAccelText;
        QList<QAction*> actionsList;
        QScopedPointer<QSettings> settings;
        QList<QAction*> m_actions;

        // UI layout related direct widgets with parents
        QGridLayout* gridLayout;
        QTableWidget* TableWidgetActions;
        QDialogButtonBox* buttonBox;
};

#endif // ACTIONSDIALOG_H
