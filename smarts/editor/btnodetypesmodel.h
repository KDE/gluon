#ifndef BTNODETYPESMODEL_H
#define BTNODETYPESMODEL_H

#include <QAbstractListModel>
#include <QList>
class btBrain;
class btEditorNodeType;
class btNodeTypesModelNode;

class btNodeTypesModel : public QAbstractItemModel
{
Q_OBJECT
public:
    btNodeTypesModel(btBrain *brain, QObject *parent = 0);
    ~btNodeTypesModel();

    QMimeData* mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &index) const;
    int columnCount(const QModelIndex &index) const;

    btNodeTypesModelNode* nodeFromIndex(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &index = QModelIndex() );
    bool insertRows(int row, int count, const QModelIndex &parent);
    
public Q_SLOTS:
    void newBehaviorTreeTypeAdded(btEditorNodeType* newType);


private:
    btEditorNodeType *nodeTypeFromIndex(const QModelIndex &index) const;
    btNodeTypesModelNode* rootNode;
    
    btNodeTypesModelNode *nodeAction;
    btNodeTypesModelNode *nodeCondition;
    btNodeTypesModelNode *nodeComposite;
    btNodeTypesModelNode *nodeDecorator;
    btNodeTypesModelNode *nodeReference;
    btBrain *m_brain;
};

#endif // BTNODETYPESMODEL_H
