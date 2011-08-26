#ifndef _BTEDITORNODE_H_
#define _BTEDITORNODE_H_

#include <QObject>

#include "../common/btnode.h"

class btTreeModel;
class QXmlStreamWriter;

class btEditorNode : public btNode 
{
    Q_OBJECT
    
public:    
    
    btEditorNode(btNodeType *type = 0, btNode *parent = 0);
    ~btEditorNode();
    
    void toXml(QXmlStreamWriter* xmlWriter, QList<btTreeModel *> behaviorTrees);
    
    QVariant data(int column) const;
    QVariant headerData(int column) const;
    
    void addDecorator(btNodeType* decorator);
    void removeDecorator(btNodeType* decorator);
    void moveDecorator(int move, btNodeType * decorator);
    int decoratorCount() const;
    QList<btNodeType*> decorators() const;
    
    void emitUpdatePropertyWidget();
    
Q_SIGNALS:
    void updatePropertyWidget(btEditorNode* node);
    
private:    
    QList<btNodeType*> m_decorators;
};

#endif
