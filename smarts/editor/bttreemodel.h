#ifndef BTTREEMODEL_H
#define BTTREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QString>
class btEditorNode;
class btBrain;

class btTreeModel : public QAbstractItemModel
{
    Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)

public:
    btTreeModel(QObject *parent = 0, btBrain* containingBrain = 0);
    ~btTreeModel();

    void setRootNode(btEditorNode *newRoot);
    btEditorNode * rootNode() const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    
    Qt::ItemFlags flags(const QModelIndex &index) const;
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QMimeData* mimeData(const QModelIndexList &indexes) const;

    bool removeRows(int position, int rows, const QModelIndex &parent);

    QString name() const;
    void setName(QString name);

    QString description() const;
    void setDescription(QString description);
    
public Q_SLOTS:
    void updateTreeModel();

Q_SIGNALS:
    void addRemoveBTNode();
    
private:
    bool moving;
    
	QString m_name;
    QString m_description;

    btEditorNode *nodeFromIndex(const QModelIndex &index) const;

    btEditorNode *m_rootNode;
    btBrain *brain;
};

#endif // BTTREEMODEL_H
