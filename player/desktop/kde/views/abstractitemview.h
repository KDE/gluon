/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#ifndef ABSTRACTITEMVIEW_H
#define ABSTRACTITEMVIEW_H

#include "overlay.h"

#include <QtGui/QWidget>
#include <QtCore/QAbstractItemModel>

class AbstractItemView : public Overlay
{
        Q_OBJECT
    public:
        explicit AbstractItemView( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );

        virtual void setModel( QAbstractItemModel* model );
        QAbstractItemModel* model() const;

    protected:
        QAbstractItemModel* m_model;
};

#endif // ABSTRACTITEMVIEW_H
