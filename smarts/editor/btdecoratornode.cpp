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

#include "btdecoratornode.h"
#include "projectparser.h"

#include <QtXml>

btDecoratorNode::btDecoratorNode(QObject* parent)
    : btEditorNodeType(parent)
{
    setNodeType(btNodeType::DecoratorNodeType);
}

btDecoratorNode::~btDecoratorNode()
{
}

bool btDecoratorNode::run(btCharacter* character)
{
    Q_UNUSED(character)
    return false;
}

void  btDecoratorNode::toDataXml(QXmlStreamWriter* xmlWriter)
{
    xmlWriter->writeStartElement("decorator");

    const QMetaObject * mo = this->metaObject();

    for (int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();

        if (propertyName == "objectName")
        {
            continue;
        }

        if (propertyName == "name")
        {
            xmlWriter->writeAttribute("name", this->property(moProperty.name()).toString());
        }
        else if (propertyName == "description")
        {
            xmlWriter->writeAttribute("description", this->property(moProperty.name()).toString());
        }
        else if (propertyName == "className")
        {
            xmlWriter->writeAttribute("nodetype", this->property(moProperty.name()).toString());
        }
    }

    for (int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
        xmlWriter->writeStartElement("property");

        xmlWriter->writeAttribute("name", propertyName);
        xmlWriter->writeAttribute("value", this->property(propertyName.toUtf8()).toString());

        xmlWriter->writeEndElement();
    }

    xmlWriter->writeEndElement(); //decorator
}

#include "btdecoratornode.moc"
