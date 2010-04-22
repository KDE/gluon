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

#include "metainfo.h"
#include "gluonobject.h"

using namespace GluonCore;

class MetaInfo::MetaInfoPrivate
{
    public:
        MetaInfoPrivate() {};
        ~MetaInfoPrivate() {};

        QHash<QString, qreal> propertyRangeMin;
        QHash<QString, qreal> propertyRangeMax;
        QHash<QString, qreal> propertyStep;
};

MetaInfo::MetaInfo(GluonObject* parent)
    : d(new MetaInfoPrivate())
{
}

MetaInfo::MetaInfo(const GluonCore::MetaInfo& other)
{
    delete(d);
}

MetaInfo::~MetaInfo()
{

}

void
MetaInfo::setPropertyRange(const QString& property, qreal min, qreal max)
{
    d->propertyRangeMin.insert(property, min);
    d->propertyRangeMax.insert(property, max);
}

bool
MetaInfo::hasPropertyRange(const QString& property) const
{
    return d->propertyRangeMin.keys().contains(property);
}

qreal
MetaInfo::propertyRangeMin(const QString& property) const
{
    // This will return 0 if we do not have a property range for this property
    // name - but anybody using it should have checked beforehand
    return d->propertyRangeMin[property];
}

qreal
MetaInfo::propertyRangeMax(const QString& property) const
{
    // This will return 0 if we do not have a property range for this property
    // name - but anybody using it should have checked beforehand
    return d->propertyRangeMax[property];
}

void
MetaInfo::removePropertyRange(const QString& property)
{
    d->propertyRangeMin.remove(property);
    d->propertyRangeMax.remove(property);
}

void
MetaInfo::setPropertyStep(const QString& property, qreal step)
{
    d->propertyStep.insert(property, step);
}

bool
MetaInfo::hasPropertyStep(const QString& property) const
{
    return d->propertyStep.keys().contains(property);
}

qreal
MetaInfo::propertyStep(const QString& property) const
{
    // This will return 0 if we do not have a property step for this property
    // name - but anybody using it should have checked beforehand
    return d->propertyStep[property];
}

void
MetaInfo::removePropertyStep(const QString& property)
{
    d->propertyStep.remove(property);
}
