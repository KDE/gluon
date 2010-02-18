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
#include "gluonobjectpropertywidgetitem.h"

#include "core/debughelper.h"
#include "core/gluonobjectfactory.h"

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT PropertyWidgetItemFactory* GluonCore::Singleton<PropertyWidgetItemFactory>::m_instance = 0;

PropertyWidgetItem*
PropertyWidgetItemFactory::create(const QString& type, QWidget* parent)
{
    DEBUG_BLOCK
    
    // First check if there's any PIW which supports the type
    foreach(const QString &thisType, piwTypes.keys())
    {
        if(thisType == type)
        {
            PropertyWidgetItem* item = piwTypes[thisType]->instantiate();
            item->setParent(parent);
            return item;
        }
    }
    
    // Then see if it's a reference type inheriting GluonObject...
    QString typeTruncated = type.left(type.length() - 1);
    foreach(const QString &thisType, GluonCore::GluonObjectFactory::instance()->objectTypeNames())
    {
        if(thisType == typeTruncated)
        {
            return new GluonObjectPropertyWidgetItem(parent);
        }
    }
    
    // Finally, throw back a Null item if we've got nothing...
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

