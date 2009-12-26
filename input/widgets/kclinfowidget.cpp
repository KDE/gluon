#include "kclinfowidget.h"

#include <QtGui/QIcon>
#include <QtGui/QMessageBox>

#include <QtGui/QPushButton>
//#include <QtGui/QSeparator>
//#include <KLocale>

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtCore/QProcess>
#include <QtGui/QVBoxLayout>
#include <QtGui/QStackedWidget>
#include <QtGui/QComboBox>

#include "kclcode.h"

KCLInfoWidget::KCLInfoWidget(QWidget *parent)
        : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_information = new QWidget;
    m_preview = new QWidget;
    QTabWidget *tab = new QTabWidget;
    tab->addTab(m_preview, QIcon("run-build-configure.png"), "preview");
    tab->addTab(m_information, QIcon("run-build-file.png"), "information");
    setupPreview();
    setupInformation();
    layout->addWidget(tab);
    setLayout(layout);
}

void KCLInfoWidget::setupPreview()
{
    QStackedWidget * widget = new QStackedWidget;
    QComboBox * combo = new QComboBox;

    foreach ( KCLInput * input, KCLDetect::inputList())
    {
        KCLInputWidget * w = new KCLInputWidget(input);
    #ifdef Q_WS_X11
        combo->addItem(KCLCode::iconDevice(input->deviceType()),input->deviceName());
    #endif
        widget->addWidget(w);

}

connect(combo,SIGNAL(currentIndexChanged(int)),widget,SLOT(setCurrentIndex(int)));
combo->setCurrentIndex(combo->count()-1);
QVBoxLayout * layout = new QVBoxLayout;
layout->addWidget(combo);
layout->addWidget(widget);
widget->setCurrentIndex(1);
m_preview->setLayout(layout);

}

void KCLInfoWidget::setupInformation()
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *info = new QLabel(tr("Some Linux distributions forbid direct access \n to the input method used by KCL(evdev) as it can causes security-related issues\n"
                                    "If you are sure, you can allow direct access by clicking here."));

    QPushButton *buttonAuthorizate = new QPushButton(QIcon("dialog-password.png"), "set permission");
    QPushButton *buttonDetect = new QPushButton(QIcon("edit-find.png"), "Detect device");

    connect(buttonAuthorizate, SIGNAL(clicked()), this, SLOT(setAuthorization()));
    connect(buttonDetect, SIGNAL(clicked()), this, SLOT(detectDevice()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(info);
    hlayout->addStretch();
    hlayout->addWidget(buttonAuthorizate);
    hlayout->addWidget(buttonDetect);

    m_model = new KCLDeviceModel(this);
    m_treeView = new QTreeView;
    m_treeView->setModel(m_model);
    m_treeView->setIconSize(QSize(22, 22));
    layout->addLayout(hlayout);
    layout->addWidget(m_treeView);
    m_information->setLayout(layout);
}

void KCLInfoWidget::setAuthorization()
{
    //TODO: Find a better way to do that(either via HAL, PolicyKit, or use X11 libs instead of evdev.
    if (QProcess::execute("kdesudo chmod -R a+rwx /dev/input/*")) {
        QMessageBox::information(this, tr("authorization success..."), "success");
    } else {
        QMessageBox::critical(this, tr("authorization failed..."), "failed");
    }
}

void KCLInfoWidget::detectDevice()
{
    m_model->clear();
    m_model->setupList();
}

#include "kclinfowidget.moc"
