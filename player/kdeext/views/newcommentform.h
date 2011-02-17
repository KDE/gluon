/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef NEWCOMMENTFORM_H
#define NEWCOMMENTFORM_H

#include <KDE/KPushButton>
#include <KDE/KTextEdit>
#include <KDE/KLocalizedString>
#include <KDE/KLineEdit>
#include <KDE/KDebug>

#include <QtGui/QGridLayout>
#include <QtCore/QModelIndex>

class NewCommentForm : public QWidget
{
        Q_OBJECT
    public:
        NewCommentForm( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        virtual ~NewCommentForm();

        void setParentIndex( QModelIndex parentIndex );

        QString titleText() const;
        void setTitleText(const QString& titleText);

        QString bodyText() const;
        void setBodyText(const QString& bodyText);

    private slots:
        void validateAndSubmit();

    signals:
        void accepted( QModelIndex parentIndex, QString title, QString body );
        void canceled();

    private:
        KLineEdit* m_titleEdit;
        KTextEdit* m_bodyEdit;
        KPushButton* m_okButton;
        KPushButton* m_cancelButton;
        QModelIndex m_parentIndex;
};

#endif // NEWCOMMENTFORM_H
