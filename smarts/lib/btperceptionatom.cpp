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

#include "btperceptionatom.h"

class btPerceptionAtom::btPerceptionAtomPrivate
{
    public:
        btPerceptionAtomPrivate()
        {
            perceptionInfo = 0;
            precision = 0;
        }
        ~btPerceptionAtomPrivate() {}
        
        btPerceptionInfo* perceptionInfo;
        qreal precision;
        QVariant knowledge;
        bool shouldUpdate;
};

btPerceptionAtom::btPerceptionAtom(QObject* parent)
    : QObject(parent)
{
    d = new btPerceptionAtomPrivate();
}

btPerceptionAtom::~btPerceptionAtom()
{
    delete(d);
}

btPerceptionInfo* btPerceptionAtom::perceptionInfo() const
{
    return d->perceptionInfo;
}

void btPerceptionAtom::setPerceptionInfo(btPerceptionInfo* newPerceptionInfo)
{
    disconnect(this, SLOT(perceptionInfoUpdate()));
    d->perceptionInfo = newPerceptionInfo;
    connect(d->perceptionInfo, SIGNAL(infoUpdated()), this, SLOT(perceptionInfoUpdated()));
}

QVariant btPerceptionAtom::knowledge() const
{
    return d->knowledge;
}

qreal btPerceptionAtom::precision() const
{
    return d->precision;
}

void btPerceptionAtom::setPrecision(const qreal& newPrecision)
{
    d->precision = newPrecision;
    d->shouldUpdate = true;
}

bool btPerceptionAtom::shouldUpdate() const
{
    return d->shouldUpdate;
}

void btPerceptionAtom::setShouldUpdate(const bool& newShouldUpdate)
{
    d->shouldUpdate = newShouldUpdate;
}

void btPerceptionAtom::perceptionInfoUpdated()
{
    if(d->shouldUpdate)
        d->knowledge = d->perceptionInfo->getAdjustedValue(d->precision);
}

#include "btperceptionatom.moc"