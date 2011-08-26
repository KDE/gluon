#ifndef BTQLISTDELEGATE_H
#define BTQLISTDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>

class btQListDeletgate : public QItemDelegate
{
    Q_OBJECT
    
public:
    btQListDeletgate(QObject *parent = 0);
    
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif