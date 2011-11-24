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

#include "btnodetype.h"
#include "btcharacter.h"

btNodeType::btNodeType(QObject * parent)
{
    Q_UNUSED(parent)
    m_parent = NULL;
}

btNodeType::~btNodeType()
{
}

void btNodeType::setName(QString name) {
    m_name = name;
}
QString btNodeType::name() const {
    return m_name;
}

void btNodeType::setDescription(QString description) {
    m_description = description;
}
QString btNodeType::description() const {
    return m_description;
}

void btNodeType::setNodeType(nodeType type) {
    m_type = type;
}
btNodeType::nodeType btNodeType::type() const
{
    if (m_type)
        return m_type;
    else
        return UnusableNodeType;
}

bool btNodeType::run(btCharacter *self)
{
    Q_UNUSED(self)
    return false;
}

btNodeType * btNodeType::copy()
{
    return NULL;
}

void btNodeType::setClassName(QString className)
{
    m_className = className;
}

QString btNodeType::className() const
{
    return m_className;
}

void btNodeType::setParentNode(btNode* node)
{
    m_parent = node;
    setParent(node);
}

btNode* btNodeType::parentNode()
{
    return m_parent;
}

void btNodeType::setPropertyDescription(QString propertyName, QString description)
{
    m_propertiesDescriptions[propertyName] = description;
}

QString btNodeType::getPropertyDescription(QString propertyName)
{
    if (m_propertiesDescriptions.contains(propertyName))
        return m_propertiesDescriptions[propertyName];

    return "";
}

void btNodeType::setPropertyDescription(QString newPropertyName, QString oldPropertyName, QString description)
{
    m_propertiesDescriptions[newPropertyName] = description;
    removePropertyDescription(oldPropertyName);
}

void btNodeType::removePropertyDescription(QString propertyName)
{
    if (m_propertiesDescriptions.contains(propertyName))
        m_propertiesDescriptions.remove(propertyName);
}

QHash<QString, QString> btNodeType::getPropertyDescriptions()
{
    return m_propertiesDescriptions;
}

#include "btnodetype.moc"
