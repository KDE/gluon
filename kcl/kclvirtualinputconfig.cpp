#include "kclvirtualinputconfig.h"
#include <QVBoxLayout>
#include <KDebug>
#include <KPushButton>
#include <KIcon>
#include <KDialog>
#include <KTitleWidget>
KCLVirtualInputConfig::KCLVirtualInputConfig(KCLVirtualInput * input ,QWidget * parent)
    :KDialog(parent)
{

    m_virtualInput = input;
    m_treeWidget= new QTreeWidget;
    m_treeWidget->setColumnCount(3);
    m_treeWidget->setRootIsDecorated(false);
    m_treeWidget->setAlternatingRowColors(true);
    setMainWidget(m_treeWidget);
    setup();
    QStringList header;
    header<<"action"<<"primary"<<"secondary";
    m_treeWidget->setHeaderLabels(header);
    m_treeWidget->resizeColumnToContents(0);
    m_treeWidget->resizeColumnToContents(1);
    m_treeWidget->resizeColumnToContents(2);



    QHBoxLayout * barLayout = new QHBoxLayout;

setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Default);

}





void KCLVirtualInputConfig::setup()
{



    foreach ( VirtualButton * button, m_virtualInput->primaryButtonList())
    {

        QTreeWidgetItem * item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0,button->name());

        item->setText(1,"-");
        item->setText(2,"-");



        //        KPushButton * primary = new KPushButton(KIcon("edit-clear-locationbar-ltr.png"),"?");
        //        KPushButton * secondary = new KPushButton(KIcon("edit-clear-locationbar-ltr.png"),"?");
        //        m_treeWidget->setItemWidget(item,1,primary);
        //    m_treeWidget->setItemWidget(item,2,secondary);
    }

    connect(m_treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(changeButton(QTreeWidgetItem*,int)));

}

void KCLVirtualInputConfig::changeButton(QTreeWidgetItem * item, int column)
{
    KDialog * dialog = new KDialog;
    dialog->setCaption("wainting");
    QWidget * main = new QWidget;
    QVBoxLayout * layout = new QVBoxLayout;
    dialog->setButtons(KDialog::None );
    KTitleWidget * title = new KTitleWidget(dialog);
    title->setPixmap(KIcon("configure.png"));
    title->setText("Press any button of any device");
    KCLButton * button = new KCLButton(KCL::Button);
    layout->addWidget(title);
    layout->addWidget(button);
    main->setLayout(layout);
    dialog->setMainWidget(main);
    setEnabled(false);
    connect(button,SIGNAL(changed()),dialog,SLOT(accept()));
    connect(dialog,SIGNAL(rejected()),button,SLOT(clear()));

    if ( dialog->exec())
    {
        item->setIcon(column,button->icon());
        item->setText(column,KCLCode::buttonName(button->code()));
        item->setToolTip(column,button->input()->deviceName());
    }
    setEnabled(true);
}



