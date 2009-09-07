#include "kalinfowidget.h"
#include <KTitleWidget>
#include <QVBoxLayout>
#include <KTabWidget>
#include <KIcon>
#include <QDir>
#include <KPushButton>
#include <QToolButton>
#include <QLabel>
#include <QMessageBox>
#include <KLocale>
#include <KComboBox>
#include "kalplayerwidget.h"
KALInfoWidget::KALInfoWidget(QWidget * parent)
    :QWidget(parent)
{

    KALEngine::instance();
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


void KALInfoWidget::setupPreview()
{
KALPlayerWidget * widget = new KALPlayerWidget;
QHBoxLayout * layout = new QHBoxLayout;
layout->addWidget(widget);
m_preview->setLayout(layout);

}
void KALInfoWidget::setupInformation()
{

    KComboBox * combo = new KComboBox;

foreach (QString device, KALEngine::instance()->deviceList())
  combo->addItem(KIcon(),device);

connect(combo,SIGNAL(activated(QString)),this,SLOT(setDevice(QString)));

    QLabel * logo = new QLabel;
    logo->setPixmap(KIcon("media-flash").pixmap(128,128));
    logo->setAlignment(Qt::AlignTop);

    QLabel *label= new QLabel ;
    QString info="";
    info+="<p>Vendor :"+QString(alGetString(AL_VENDOR))+ "</p>";
    info+="<p>Version :"+QString(alGetString(AL_VERSION)) + "</p>";
    info+="<p>Renderer :"+QString(alGetString(AL_RENDERER)) + "</p>";

    //info+="<p>Vendor :"+QString(alcGetString(m_alEngine->AL_DEFAULT_DEVICE_SPECIFIER))+ "</p>";
    //info+="<p>Version :"+QString(alcGetString(AL_VERSION)) + "</p>";
    //info+="<p>Renderer :"+QString(alcGetString(AL_RENDERER)) + "</p>";

    label->setText(info);
    label->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    QHBoxLayout * h = new QHBoxLayout;
    h->addWidget(logo);
    h->addWidget(label);
    QVBoxLayout * lv = new QVBoxLayout;
    lv->addLayout(h);
    lv->addWidget(combo);
   lv->addStretch();
    m_information->setLayout(lv);

}


void KALInfoWidget::setDevice(const QString& device)
{
    KALEngine::instance()->setDevice(device);
}

