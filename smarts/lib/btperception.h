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

#ifndef BTPERCEPTION_H
#define BTPERCEPTION_H

#include <QtCore/QObject>
#include <QVector3D>

#include "btperceptionatom.h"
#include "btperceptionviewcone.h"
#include "btcharacter.h"

Q_DECLARE_METATYPE(QList<btPerceptionViewcone*>);
Q_DECLARE_METATYPE(QList<btPerceptionAtom*>);

class btPerception : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal knowledgePrecision READ knowledgePrecision WRITE setKnowledgePrecision)
    Q_PROPERTY(qreal perceptionLimit READ perceptionLimit WRITE setPerceptionLimit)
    Q_PROPERTY(QList<btPerceptionViewcone*> viewCones READ viewCones WRITE setViewCones)
    // the list of perception atoms is not a property, as it is dynamically created when accessing individual pieces of information
    
    public:
        btPerception(QObject* parent = 0);
        ~btPerception();
        
        /**
         * How precise the knowledge of an item found inside the perception limit is, if it is not
         * inside a view cone. This defaults to 0, as the perception limit is normally used
         * only as a potentiality check. If you set this above zero, a perception atom will be
         * given this precision if it is found insive the perception limit, but not inside a view
         * cone.
         * 0 is no precision at all, 1.0 is full precision
         */
        qreal knowledgePrecision() const;
        void setKnowledgePrecision(const qreal& newKnowledgePrecision);
        
        /**
         * The limit of the character's perception. If left at 0, the limit will be the entire level.
         * Please note that this can potentially be very expensive, depending on level size.
         */
        qreal perceptionLimit() const;
        void setPerceptionLimit(const qreal& newPerceptionLimit);
        
        QList<btPerceptionViewcone*> viewCones() const;
        void setViewCones(const QList<btPerceptionViewcone*> newViewCones);
		void addViewCone(btPerceptionViewcone * viewcone);
        
        QList<btPerceptionAtom*> perceptionAtoms() const;
        btPerceptionAtom* perceptionAtom(const QString& name) const;
		void addPerceptionAtom(btPerceptionAtom * perceptionAtom);
        
    private:
        class btPerceptionPrivate;
        btPerceptionPrivate* d;
};

#endif // BTPERCEPTION_H
