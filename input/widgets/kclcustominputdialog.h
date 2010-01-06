#ifndef KCLCUSTOMINPUTWIDGET_H
#define KCLCUSTOMINPUTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QTabWidget>
#include <QtCore/QList>
#include <QtGui/QTreeWidget>
#include <QtGui/QDialog>

#include <QtGui/QTreeWidgetItem>

#include "kclpressbutton.h"
#include "kclcustominput.h"

class KCLCustomInputDialog : public QDialog
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
