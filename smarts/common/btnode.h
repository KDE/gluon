#ifndef BTNODE_H
#define BTNODE_H

#include <QObject>
#include <QList>

#include "../lib/btlib_export.h"

class QString;
class QVariant;
class btNodeType;
class btCharacter;

class BT_LIB_EXPORT btNode : public QObject
{
Q_OBJECT;
Q_PROPERTY(QString name READ name WRITE setName);
Q_PROPERTY(QString description READ description WRITE setDescription);

public:
    btNode(btNodeType *type = 0, btNode *parent = 0);
    ~btNode();
    
    bool runBehavior(btCharacter *self);

	virtual void appendChild(btNode * child);
    virtual void insertChild(int pos, btNode* child);
    virtual void removeChild(int row);
    virtual void removeChild(btNode* child);
    virtual void doneParsingChildren();
	
	virtual btNode *child(int row);
    virtual QList<btNode*> children();
	virtual int childCount() const;
	virtual btNode *parentNode();
    virtual void setParentNode(btNode * node);
    
    
    virtual int columnCount() const;
    virtual int row() const;
	
    virtual void setName(QString name);
    virtual QString name() const;
    virtual void setDescription(QString description);
    virtual QString description() const;
	virtual void setType(btNodeType *newType);
    virtual btNodeType* type() const;

/*    virtual void addDecorator(btNodeType* decorator);
    virtual void removeDecorator(btNodeType* decorator);
    virtual void 
    virtual int decoratorCount() const;
    QList<btNodeType*> decorators() const;*/

private:
	btNodeType *m_type;
	
	btNode *m_parent;
    QList<btNode *> m_children;
	
	QString m_name;
    QString m_description;
	QList<QVariant> nodeData;
    //QList<btNodeType*> m_decorators;
    
    bool run(btCharacter *self);
};

#endif // BTNODE_H
