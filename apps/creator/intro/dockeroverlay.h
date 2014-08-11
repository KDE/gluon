/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
 * Copyright (c) 2013 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef DOCKEROVERLAY_H
#define DOCKEROVERLAY_H

#include <QtQuick/QQuickItem>

class DockerOverlay : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(QString dockerName READ dockerName WRITE setDockerName NOTIFY dockerNameChanged)

        public:
            DockerOverlay(QQuickItem* parent = 0);
            virtual ~DockerOverlay();

            QString dockerName() const;
            void setDockerName( const QString& name );

        Q_SIGNALS:
            void dockerNameChanged();

        private:
            class Private;
            Private* const d;
};

#endif // DOCKEROVERLAY_H
