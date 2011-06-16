#ifndef BTNODEMODEL_H
#define BTNODEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>

class btEditorNodeType;

class btnodemodel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString classname READ classname WRITE setClassname)

public:
    btnodemodel(btEditorNodeType * nodetype,QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index,const QVariant &value, int role = Qt::EditRole);

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    QString name() const;
    void setName(QString name);

    QString description() const;
    void setDescription(QString description);

    QString classname() const;
    void setClassname(QString classname);
    
Q_SIGNALS:
    void updatePropertyWidget();

private:
    btEditorNodeType *     node;
};

#endif // BTNODEMODEL_H
