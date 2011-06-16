#ifndef BTQVARIANTLISTWIDGET_H
#define BTQVARIANTLISTWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>

class btQVariantListWidget : public QWidget
{
    Q_OBJECT
public:
    btQVariantListWidget(bool enabled, QWidget * parent = 0);
    ~btQVariantListWidget();
    void setupActions();
    void addItem(QListWidgetItem * item);
    Qt::ItemFlags returnItemFlags();

Q_SIGNALS:
    void itemAdded(QListWidgetItem * item);
    void itemRemoved(QListWidgetItem * item, int index);
    void itemChanged(QListWidgetItem * item, int index);
    
public Q_SLOTS:
    void insertItem();
    void removeItem();
    void changeItem(QListWidgetItem * item);
    
private:
    QVBoxLayout*        mainLayout;
    QHBoxLayout*        buttonLayout;
    QListWidget*        listWidget;
    QPushButton*        removeButton;
    QPushButton*        addButton;
};

#endif // TREESELECTORDIALOG_H
