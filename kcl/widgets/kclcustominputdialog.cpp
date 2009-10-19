#include "kclcustominputdialog.h"

#include "kclcode.h"
#include "kclcustominput.h"
#include "kclinput.h"
#include "kclpressbutton.h"

#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <KLocale>
#include <KTitleWidget>
#include <KDebug>
KCLCustomInputDialog::KCLCustomInputDialog( QWidget * parent)
    :KDialog(parent)
{
    m_tabWidget = new QTabWidget;

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_tabWidget);
    QWidget * main =new QWidget;
    main->setLayout(layout);
    setMainWidget(main);

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
        tree->setColumnCount(3);
        tree->headerItem()->setText(0,i18n("action"));
        tree->headerItem()->setText(1,i18n("code"));
        tree->headerItem()->setText(2,i18n("device"));

        tree->setRootIsDecorated(false);
        tree->setAlternatingRowColors(true);
        connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(changeItem(QTreeWidgetItem*,int)));

        foreach (const QString &name, input->buttonNameList())
        {

            QTreeWidgetItem * item = new QTreeWidgetItem(tree);
            item->setText(0,name);
            item->setText(1,KCLCode::buttonName(input->codeAt(name,KCL::Key)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::Key)->deviceType()));
            item->setText(2,input->inputAt(name,KCL::Key)->deviceName());
        }

        foreach (const QString &name, input->absAxisNameList())
        {

            QTreeWidgetItem * item = new QTreeWidgetItem(tree);

            item->setText(0,name);
            item->setText(1,KCLCode::absAxisName(input->codeAt(name,KCL::AbsoluAxis)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::AbsoluAxis)->deviceType()));
            item->setText(2,input->inputAt(name,KCL::AbsoluAxis)->deviceName());
        }

        foreach (const QString &name, input->relAxisNameList())
        {


            QTreeWidgetItem * item = new QTreeWidgetItem(tree);
            item->setText(0,name);
            item->setText(1,KCLCode::relAxisName(input->codeAt(name,KCL::RelativeAxis)));
            item->setIcon(1,KCLCode::iconDevice(input->inputAt(name,KCL::RelativeAxis)->deviceType()));
            item->setText(2,input->inputAt(name,KCL::RelativeAxis)->deviceName());

        }

        m_tabWidget->addTab(tree,"");
        tree->expandAll();
    }
}
void KCLCustomInputDialog::changeItem(QTreeWidgetItem * item,int col)
{
    kDebug()<<"will change...";

    QTreeWidget * tree = qobject_cast<QTreeWidget*>(sender());
    KCLCustomInput * input = m_inputList.at(m_tabWidget->currentIndex());

    KDialog *dialog = new KDialog;
    dialog->setCaption("Waiting...");

    QWidget *main = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    dialog->setButtons(KDialog::None);
    //
    KTitleWidget *title = new KTitleWidget(dialog);
    title->setPixmap(KIcon("configure.png"));
    title->setText("Press or move anything from any device");

    KCLPressButton * button = new KCLPressButton;

    if ( input->buttonNameList().contains(item->text(0)))
        button->setButtonDetect(true);

    if ( input->absAxisNameList().contains(item->text(0)))
        button->setAbsAxisDetect(true);

    if ( input->relAxisNameList().contains(item->text(0)))
        button->setRelAxisDetect(true);


    layout->addWidget(title);
    layout->addWidget(button);
    main->setLayout(layout);
    dialog->setMainWidget(main);
    setEnabled(false);
    button->startDetection();
    connect(button,SIGNAL(changed()),dialog,SLOT(accept()));

    if ( dialog->exec())
    {
        kDebug()<<"accept...";
        if ( input->buttonNameList().contains(item->text(0)))
            input->setButton(item->text(0),button->input(),button->code());

        if ( input->absAxisNameList().contains(item->text(0)))
            input->setAbsAxis(item->text(0),button->input(),button->code());

        if ( input->relAxisNameList().contains(item->text(0)))
            input->setRelAxis(item->text(0),button->input(),button->code());


        setupTab();
    }
    setEnabled(true);



}
