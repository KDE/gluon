/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QtWidgets/QWidget>

#include <core/privatepointer.h>

class ActionWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit ActionWindow( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        ~ActionWindow();

    private Q_SLOTS:
        void deviceChanged( int index );
        void parameterChanged( int index );
        void valueChanged();
        void pressed();
        void released();
        void triggered();

    GLUON_PRIVATE_POINTER;
};

#endif // ACTIONWINDOW_H
