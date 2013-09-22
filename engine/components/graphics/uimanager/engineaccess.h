/*
 *   Copyright 2010 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ENGINEACCESS_H
#define ENGINEACCESS_H

#include <QtCore/QObject>

#include <QtScript/QScriptValue>

namespace GluonEngine
{

    class UiManagerComponent;

    class EngineAccess : public QObject
    {
            Q_OBJECT

        public:
            EngineAccess( UiManagerComponent* parent );
            ~EngineAccess();

            Q_INVOKABLE void setEngine( QScriptValue val );

        private:
            UiManagerComponent* m_component;

    };
}

#endif