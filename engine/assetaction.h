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
 */

#ifndef GLUONENGINE_ASSETACTION_H
#define GLUONENGINE_ASSETACTION_H

#include <QtCore/QObject>

class QIcon;
namespace GluonEngine
{

    class AssetAction : public QObject
    {
            Q_OBJECT
            Q_PROPERTY( QIcon icon READ icon WRITE setIcon NOTIFY iconChanged )
            Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged )

        public:
            ~AssetAction();
            AssetAction( const QString& name = QString(), QObject* parent = 0 );

            QIcon icon() const;
            QString name() const;

        public Q_SLOTS:
            void setIcon( const QIcon& icon );
            void setName( const QString& name );
            void trigger();

        Q_SIGNALS:
            void iconChanged();
            void nameChanged();
            void triggered();

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONENGINE_ASSETACTION_H
