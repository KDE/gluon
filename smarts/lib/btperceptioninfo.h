/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef BTPERCEPTIONINFO_H
#define BTPERCEPTIONINFO_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtGui/QVector3D>

class btBrain;

class btPerceptionInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionUpdated)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusUpdated)
    
    public:
        btPerceptionInfo(QObject* parent);
        ~btPerceptionInfo();
        
        virtual QVector3D position() const;
        virtual void setPosition(const QVector3D& newPosition);
        
        virtual qreal radius() const;
        virtual void setRadius(const qreal& newRadius);
        
        virtual QVariant getAdjustedValue(qreal precision) const = 0;
        
    Q_SIGNALS:
        void infoUpdated();
        void positionUpdated(QVector3D);
        void radiusUpdated(qreal);
        
    private:
        class btPerceptionInfoPrivate;
        btPerceptionInfoPrivate* d;
};

#endif // BTPERCEPTIONINFO_H
