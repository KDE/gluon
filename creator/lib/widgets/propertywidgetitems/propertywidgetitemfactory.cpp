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

#include <core/debughelper.h>

#include "nullpropertywidgetitem.h"
#include "textpropertywidgetitem.h"
#include "vectorpropertywidgetitem.h"
#include "boolpropertywidgetitem.h"
#include "floatpropertywidgetitem.h"
#include "intpropertywidgetitem.h"
#include "qsizefpropertywidgetitem.h"
#include "colorpropertywidgetitem.h"
#include "quaternionpropertywidgetitem.h"

using namespace GluonCreator;

template<> PropertyWidgetItemFactory* GluonCore::Singleton<PropertyWidgetItemFactory>::m_instance = 0;

PropertyWidgetItem* PropertyWidgetItemFactory::create(const QString& type, QWidget* parent)
{
    DEBUG_BLOCK

    if(type == "QString")
        return new TextPropertyWidgetItem(parent);
    if(type == "QVector3D")
        return new VectorPropertyWidgetItem(parent);
    if(type == "bool")
        return new BoolPropertyWidgetItem(parent);
    if(type == "float")
        return new FloatPropertyWidgetItem(parent);
    if(type == "int")
        return new IntPropertyWidgetItem(parent);
    if(type == "QSizeF")
        return new QSizeFPropertyWidgetItem(parent);
    if(type == "QColor")
        return new ColorPropertyWidgetItem(parent);
    if(type == "QQuaternion")
        return new QuaternionPropertyWidgetItem(parent);

    DEBUG_TEXT(QString("Attempting to instantiate unknown property widget item of type %1").arg(type));

    return new NullPropertyWidgetItem(parent);

}

