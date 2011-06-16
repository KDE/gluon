#ifndef BTFACTORY_H
#define BTFACTORY_H

#include <QObject>
#include <QHash>
#include <QtXml/QDomNode>

#include "btlib_export.h"

class btNode;
class btBrain;

class BT_LIB_EXPORT btFactory : public QObject
{
    Q_OBJECT
    
public:
    static btFactory* instance();
    
    btNode* newObject(QString className);
    btNode* newObject(QDomNode xmlNode, btNode* parentNode, btBrain* brain);
    
    btNode* createRootNode(QDomNode xmlNode, btBrain* brain);
    
    void addProperty(btNode* node, QDomNode xNode, btBrain* brain);
    void initNodeType(QDomNode xmlNode);
    
    btNode * getRegisteredNodeType(QString className);
    
    void registerNodeType(btNode * newType);
    void registerNodeType(btNode * newType, QString className);
    
private:    
    btFactory();
    
    QHash<QString, btNode*> m_nodeTypes;
};

template<class T>
class BT_LIB_EXPORT Registration
{

public:
    Registration(T* newNode)
    {
        btFactory::instance()->registerNodeType(newNode);
    }
};

#define REGISTER_NODETYPE(NEWNODE) \
Registration<NEWNODE> NEWNODE ## _registration_(new NEWNODE());

#endif // BTABSTRACTFACTORY_H
