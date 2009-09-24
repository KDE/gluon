#ifndef KCLCUSTOMINPUTWIDGET_H
#define KCLCUSTOMINPUTWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QList>
#include <QTreeWidget>
#include <KDialog>
#include <QTreeWidgetItem>
#include "kclpressbutton.h"
#include "../kclcustominput.h"

class KCLCustomInputDialog : public KDialog
{
    Q_OBJECT
public:
    KCLCustomInputDialog(QWidget* parent=0);
    void addCustomInput(KCLCustomInput * input);

    protected:
    void setupTab();

    protected slots:
    void changeItem(QTreeWidgetItem * item, int col);

private:
    QTabWidget * m_tabWidget;
    QList <KCLCustomInput*> m_inputList;
};

#endif // KCLCUSTOMINPUTWIDGET_H
