#include "btnodetype.h"
#include "btcharacter.h"
#include <QtCore/QDebug>

btNodeType::btNodeType(QObject * parent)
{
    m_parent = NULL;
}

btNodeType::~btNodeType()
{
}

void btNodeType::setName(QString name) { m_name = name; }
QString btNodeType::name() const { return m_name; }

void btNodeType::setDescription(QString description) { m_description = description; }
QString btNodeType::description() const { return m_description; }

void btNodeType::setNodeType(nodeType type){m_type = type;}
btNodeType::nodeType btNodeType::type() const
{
    if(m_type)
        return m_type;
    else
        return UnusableNodeType;
}

bool btNodeType::run(btCharacter *self)
{
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
    this->setParent(node);
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
    if(m_propertiesDescriptions.contains(propertyName))
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
    if(m_propertiesDescriptions.contains(propertyName))
        m_propertiesDescriptions.remove(propertyName);
}

QHash<QString, QString> btNodeType::getPropertyDescriptions()
{
    return m_propertiesDescriptions;
}

#include "btnodetype.moc"
