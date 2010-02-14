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

#include "propertywidgetitemfactory.h"
#include "nullpropertywidgetitem.h"

#include <core/debughelper.h>

using namespace GluonCreator;

template<> PropertyWidgetItemFactory* GluonCore::Singleton<PropertyWidgetItemFactory>::m_instance = 0;

PropertyWidgetItem*
PropertyWidgetItemFactory::create(const QString& type, QWidget* parent)
{
    DEBUG_BLOCK
    
    foreach(const QString &thisType, piwTypes.keys())
    {
        if(thisType == type)
        {
            PropertyWidgetItem* item = piwTypes[thisType]->instantiate();
            item->setParent(parent);
            return item;
        }
    }

    DEBUG_TEXT(QString("Attempting to instantiate unknown property widget item of type %1").arg(type));

    return new NullPropertyWidgetItem(parent);
}

void
PropertyWidgetItemFactory::registerNewPIW(PropertyWidgetItem* newPIW)
{
    if(newPIW)
    {
        foreach(const QString &type, newPIW->supportedDataTypes())
        {
            piwTypes[type] = newPIW;
        }
    }
}

