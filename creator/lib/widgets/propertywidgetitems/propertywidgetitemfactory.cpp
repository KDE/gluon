/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#include "qrealpropertywidgetitem.h"

using namespace GluonCreator;

template<> PropertyWidgetItemFactory* GluonCore::Singleton<PropertyWidgetItemFactory>::m_instance = 0;

PropertyWidgetItem* PropertyWidgetItemFactory::create(const QString& type, QWidget* parent)
{
    DEBUG_BLOCK

    if (type == "QString")
        return new TextPropertyWidgetItem(parent);
    if (type == "QVector3D")
        return new VectorPropertyWidgetItem(parent);
    if (type == "bool")
        return new BoolPropertyWidgetItem(parent);
    if (type == "float")
        return new FloatPropertyWidgetItem(parent);
    if (type == "int")
        return new IntPropertyWidgetItem(parent);
    if (type == "QSizeF")
        return new QSizeFPropertyWidgetItem(parent);
    if (type == "QColor")
        return new ColorPropertyWidgetItem(parent);
    if (type == "QQuaternion")
        return new QuaternionPropertyWidgetItem(parent);
	if(type == "qreal")
		return new QRealPropertyWidgetItem(parent);

    DEBUG_TEXT(QString("Attempting to instantiate unknown property widget item of type %1").arg(type));

    return new NullPropertyWidgetItem(parent);

}

