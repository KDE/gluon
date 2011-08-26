#ifndef BTNODETYPE_H
#define BTNODETYPE_H

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include "btnode.h"
#include "btcharacter.h"
#include <smarts/lib/btlib_export.h>

class BT_LIB_EXPORT btNodeType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(nodeType type READ type WRITE setNodeType)
    Q_PROPERTY(QString className READ className WRITE setClassName )
    Q_ENUMS(nodeType)

public:

    enum nodeType
    {
        UnusableNodeType = 0,
        ActionNodeType,
        CompositeNodeType,
        ConditionNodeType,
        ReferenceNodeType,
        DecoratorNodeType
    };

    Q_INVOKABLE btNodeType(QObject* parent = 0);
    ~btNodeType();

    virtual void appendingChild(int index){};
    virtual void removingChild(int index){};
    virtual void childrenAdded(){};
    
    virtual void setName(QString name);
    virtual QString name() const;
    virtual void setDescription(QString description);
    virtual QString description() const;
    virtual nodeType type() const;

    virtual void setNodeType(nodeType type);
    virtual bool run(btCharacter *self);
    virtual btNodeType * copy();
    virtual QString className() const;
    virtual void setClassName(QString className);
    
    void setPropertyDescription(QString propertyName, QString description);
    void setPropertyDescription(QString newPropertyName, QString oldPropertyName, QString description);
    void removePropertyDescription(QString propertyName);
    QString getPropertyDescription(QString propertyName);
    QHash<QString, QString> getPropertyDescriptions();
    
    void setParentNode(btNode* node);
    /**
     * ParentNode() returns the node which contains the list of childnodes relevant to you.
     * @return the parent node
     */
    btNode* parentNode();

private:
    
    QString m_name;
    QString m_description;
    QString m_className;
    btNode* m_parent;
    nodeType m_type;
    QHash<QString, QString> m_propertiesDescriptions;
};

#endif // BTNODETYPE_H
