#include "kclinfowidget.h"
#include <QVBoxLayout>
#include <KIcon>
#include <KPushButton>
#include <QLabel>
#include <KLocale>
#include <QProcess>
#include <KMessageBox>
#include <QGroupBox>
#include <KSeparator>
KCLInfoWidget::KCLInfoWidget(QWidget * parent)
    :QWidget(parent)
{

    QVBoxLayout * layout = new QVBoxLayout;


    m_information = new QWidget;
    m_preview = new QWidget;
    KTabWidget *tab = new KTabWidget;
    tab->addTab(m_preview,KIcon("run-build-configure.png"),"preview");
    tab->addTab(m_information,KIcon("run-build-file.png"),"information");
    setupPreview();
    setupInformation();
    layout->addWidget(tab);
    setLayout(layout);

}
void KCLInfoWidget::setupPreview()
{
QVBoxLayout * layout = new QVBoxLayout;

QHBoxLayout * layoutButton = new QHBoxLayout;
QHBoxLayout * layoutAbsolu = new QHBoxLayout;
QHBoxLayout * layoutRelatif = new QHBoxLayout;


KCLButton * button = new KCLButton(KCL::Button);
KCLButton * axis = new KCLButton(KCL::AbsoluAxis);
KCLButton * rel = new KCLButton(KCL::AbsoluAxis);

layoutButton->addWidget(button);
layoutAbsolu->addWidget(axis);
layoutRelatif->addWidget(rel);

layout->addLayout(layoutButton);
layout->addLayout(layoutAbsolu);
layout->addLayout(layoutRelatif);
layout->addStretch();
m_preview->setLayout(layout);








}
void KCLInfoWidget::setupInformation()
{
 QVBoxLayout *layout = new QVBoxLayout;

    QLabel * info = new QLabel(i18n("Some linux distribution forbid direct access \n to evdev, because it's a securty problem.\n"
                                    "If you are sure, you can allow direct access by clicking here"));
    KPushButton * buttonAuthorizate = new KPushButton(KIcon("dialog-password.png"),"set permission");
    KPushButton * buttonDetect = new KPushButton(KIcon("edit-find.png"),"Detect device");

    connect(buttonAuthorizate,SIGNAL(clicked()),this,SLOT(setAuthorization()));
    connect(buttonDetect,SIGNAL(clicked()),this,SLOT(detectDevice()));
    QHBoxLayout * hlayout = new QHBoxLayout;
    hlayout->addWidget(info);
    hlayout->addStretch();
    hlayout->addWidget(buttonAuthorizate);
    hlayout->addWidget(buttonDetect);

    m_model = new KCLDeviceModel;
    m_treeView = new QTreeView;
    m_treeView->setModel(m_model);
    m_treeView->setIconSize(QSize(22,22));
    layout->addLayout(hlayout);
    layout->addWidget(m_treeView);
    m_information->setLayout(layout);
}
void KCLInfoWidget::setAuthorization()
{
    //MUST BE CHANGE !!!!!!!!!!!!!!!!!!!!!
    if ( QProcess::execute("kdesudo chmod -R a+rwx /dev/input/*"))
        KMessageBox::information(this,i18n("authorization success..."),"success");
    else
        KMessageBox::error(this,i18n("authorization failed..."),"failed");

}
void KCLInfoWidget::detectDevice()
{
    m_model->clear();
    m_model->setupList();

}
