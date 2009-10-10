#ifndef KCLCUSTOMINPUTWIDGET_H
#define KCLCUSTOMINPUTWIDGET_H

#include <QList>
#include <KDialog>

class KCLCustomInput;
class QTabWidget;
class QTreeWidgetItem;

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
