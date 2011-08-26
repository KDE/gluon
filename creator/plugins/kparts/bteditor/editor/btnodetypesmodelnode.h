#ifndef BTNODETYPESMODELNODE_H
#define BTNODETYPESMODELNODE_H

#include <QVariant>
#include <QList>
#include <QString>
class btEditorNodeType;

class btNodeTypesModelNode
{
public:
    btNodeTypesModelNode(btEditorNodeType *data = 0, btNodeTypesModelNode *parent = 0);
    ~btNodeTypesModelNode();

    void appendChild(btNodeTypesModelNode *child);
    btNodeTypesModelNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    btNodeTypesModelNode *parent();

    btEditorNodeType *nodeType() const;
    void setNodeType(btEditorNodeType *nodeType);

    void setName(QString name);
    QString name() const;

    void deleteChild(int row);
    
private:
    QString m_name;
    btEditorNodeType *nodeData;
    QList<btNodeTypesModelNode *> children;
    btNodeTypesModelNode *parentNode;
};

#endif // BTNODETYPESMODELNODE_H
