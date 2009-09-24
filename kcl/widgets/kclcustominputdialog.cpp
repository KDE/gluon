#include "kclcustominputdialog.h"
#include <QVBoxLayout>

KCLCustomInputDialog::KCLCustomInputDialog( QWidget * parent)
    :QDialog(parent)
{
    m_tabWidget = new QTabWidget;

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_tabWidget);
    setLayout(layout);

}
void KCLCustomInputDialog::addCustomInput(KCLCustomInput * input)
{
    m_inputList.append(input);
    setupTab();

}

void KCLCustomInputDialog::setupTab()
{
    m_tabWidget->clear();



    foreach ( KCLCustomInput * input, m_inputList)
    {
        QTreeWidget * tree = new QTreeWidget;
        tree->setColumnCount(2);
        tree->setRootIsDecorated(false);
        tree->setAlternatingRowColors(true);
        connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(changeItem(QTreeWidgetItem*,int)));

                foreach (QString name, input->buttonNameList())
        {

            QTreeWidgetItem * item = new QTreeWidgetItem(tree);
            item->setText(0,name);
            item->setText(1,KCLCode::buttonName(input->codeAt(name,KCL::Key)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::Key)->deviceType()));

        }

        foreach (QString name, input->absAxisNameList())
        {

            QTreeWidgetItem * item = new QTreeWidgetItem(tree);

            item->setText(0,name);
            item->setText(1,KCLCode::absAxisName(input->codeAt(name,KCL::AbsoluAxis)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::AbsoluAxis)->deviceType()));

        }

        foreach (QString name, input->relAxisNameList())
        {


            QTreeWidgetItem * item = new QTreeWidgetItem(tree);
            item->setText(0,name);
            item->setText(1,KCLCode::relAxisName(input->codeAt(name,KCL::RelatifAxis)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::RelatifAxis)->deviceType()));

        }

        m_tabWidget->addTab(tree,"");
        tree->expandAll();
    }
}
void KCLCustomInputDialog::changeItem(QTreeWidgetItem * item,int col)
{
kDebug()<<"will change...";










}
