/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include <QModelIndex>
#include <QGraphicsWidget>

namespace Plasma
{
    class PushButton;
    class LineEdit;
    class TextEdit;
};

class NewCommentForm : public QGraphicsWidget
{
        Q_OBJECT

    public:
        NewCommentForm(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);
        virtual ~NewCommentForm();
        void setParentIndex(QModelIndex parentIndex);

    private:
        Plasma::LineEdit *m_titleEdit;
        Plasma::TextEdit *m_bodyEdit;
        Plasma::PushButton *m_okButton;
        Plasma::PushButton *m_cancelButton;
        QModelIndex m_parentIndex;

    private slots:
        void validateAndSubmit();

    signals:
        void accepted(QModelIndex parentIndex, QString title, QString body);
        void canceled();
};

#endif // NEWCOMMENTFORM_H
