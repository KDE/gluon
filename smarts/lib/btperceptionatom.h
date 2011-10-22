/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef BTPERCEPTIONATOM_H
#define BTPERCEPTIONATOM_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "btperceptioninfo.h"

class btPerceptionAtom : public QObject
{
    Q_OBJECT
    Q_PROPERTY(btPerceptionInfo* perceptionInfo READ perceptionInfo WRITE setPerceptionInfo)
    Q_PROPERTY(QVariant knowledge READ knowledge)
    Q_PROPERTY(qreal precision READ precision WRITE setPrecision)
    Q_PROPERTY(bool shouldUpdate READ shouldUpdate WRITE setShouldUpdate)
    
    public:
        btPerceptionAtom(QObject* parent = 0);
        ~btPerceptionAtom();
        
        btPerceptionInfo* perceptionInfo() const;
        void setPerceptionInfo(btPerceptionInfo* newPerceptionInfo);
        
        QVariant knowledge() const;

        /**
         * The precision by which the piece of information is known.
         * This will automatically set shouldUpdate to true. If this is not
         * desirable, remember to manually shouldUpdate to false.
         * 
         * @see setShouldUpdate()
         */
        qreal precision() const;
        void setPrecision(const qreal& newPrecision);
        
        /**
         * Setting shouldUpdate to true will cause the atom to update itself
         * when the information is next updated. If you wish it to update
         * immediately please call the perceptionInfoUpdated slot.
         * 
         * @see perceptionInfoUpdated()
         */
        bool shouldUpdate() const;
        void setShouldUpdate(const bool& newShouldUpdate);
        
    public Q_SLOTS:
        void perceptionInfoUpdated();
        
    private:
        class btPerceptionAtomPrivate;
        btPerceptionAtomPrivate* d;
};

#endif // BTPERCEPTIONATOM_H
