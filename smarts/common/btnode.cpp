#include <QString>
#include <QVariant>
#include "btnode.h"
#include "btnodetype.h"
#include "btcharacter.h"
#include <QtCore/QDebug>

btNode::btNode(btNodeType *type, btNode *parent) : QObject(parent)
{
    
    this->m_type = type;
    
    if(type)
    {
        m_type->setParentNode(this);
    }
    
    this->m_parent = parent;
    if(parent)
    {
		parent->appendChild(this);
    }
}

btNode::~btNode()
{
    qDeleteAll(m_children);
}

bool btNode::runBehavior(btCharacter* self)
{    
/*if(m_type)
    {
        if(!m_type->run(self))
        {
            return false;
        }
    }
    
    return true;*/
    
    if(!self->continueThinking())
    {
        qDebug() << "character requested stopping";
        return false;
    }
        
    return run(self);
}

bool btNode::run(btCharacter* self)
{    
    if(m_type)
    {
        if(!m_type->run(self))
        {
            return false;
        }
    }
    
    return true;
}

void btNode::appendChild(btNode *child)
{
    m_children.append(child);
    //has to be in the list, before this function is called
    m_type->appendingChild(m_children.count()-1);
    child->setParentNode(this);
}

void btNode::removeChild(int row)
{
    //has to be removed from the list before it is removed from the m_children list
    m_type->removingChild(row);
    m_children.removeAt(row);
}

btNode *btNode::child(int row)
{
    return m_children.value(row);
}

int btNode::childCount() const
{
    return m_children.count();
}

btNode *btNode::parentNode()
{
	return m_parent;
}

void btNode::setName(QString name) { m_name = name; }
QString btNode::name() const { return m_name; }

void btNode::setDescription(QString description) { m_description = description; }
QString btNode::description() const
{
    if(m_description.isEmpty())
        return "";
    else
        return m_description;
}

void btNode::setType(btNodeType *type)
{
    delete(m_type);
    m_type = type;
    m_type->setParentNode(this);
}
btNodeType *btNode::type() const { return m_type; }

/*void btNode::addDecorator(btNodeType* decorator) 
{
    m_decorators.append(decorator); 
    decorator->setParentNode(this);
}
void btNode::removeDecorator(btNodeType* decorator) { m_decorators.removeAll(decorator); }
int btNode::decoratorCount() const { return m_decorators.count(); }
QList<btNodeType*> btNode::decorators() const { return m_decorators; }
*/
void btNode::setParentNode(btNode* node)
{    
    m_parent = node;
    this->setParent(node);
}

void btNode::doneParsingChildren()
{
    m_type->childrenAdded();
}

void btNode::removeChild(btNode* child)
{
    for (int i = 0; i < this->childCount(); i++) 
    {
        if(this->child(i) == child)
        {
            this->removeChild(i);
            break;
        }
    }
}

int btNode::columnCount() const
{
    return 3;
}

int btNode::row() const
{
	if(m_parent)
        return m_parent->m_children.indexOf(const_cast<btNode*>(this));
	
	return 0;
}

void btNode::insertChild(int pos, btNode* child)
{
    m_children.insert(pos, child);
    m_type->appendingChild(pos);
    child->setParentNode(this);
}

QList<btNode*> btNode::children()
{
    return m_children;
}

#include "btnode.moc"
