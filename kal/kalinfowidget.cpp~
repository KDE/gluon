#include "kalinfowidget.h"
#include <KTitleWidget>
#include <QVBoxLayout>
#include <KTabWidget>
#include <KIcon>
#include <QDir>
#include <KPushButton>
KALInfoWidget::KALInfoWidget(QWidget * parent)
        :QWidget(parent)
{

QVBoxLayout * layout = new QVBoxLayout;


   m_information = new QWidget;
   m_preview = new QWidget;
   KTabWidget *tab = new KTabWidget;
tab->addTab(m_preview,KIcon("run-build-configure.png"),"preview");
   tab->addTab(m_information,KIcon("run-build-file.png"),"information");


setupPreview();

layout->addWidget(tab);


setLayout(layout);
}

void KALInfoWidget::setupComboBox()
{

    m_soundComboBox = new QComboBox;
   QString path("/usr/share/sounds");
    QDir event(path);
    QStringList filter;
    filter<<"*.ogg"<<"*.wav";
    foreach  ( QString name, event.entryList(filter,QDir::Files))
    {
m_soundComboBox->addItem(KIcon("audio-x-generic.png"),name);
    }

}
void KALInfoWidget::setupPreview()
{

setupComboBox();
KPushButton * button = new KPushButton(KIcon("media-playback-start.png"),"play");
QVBoxLayout * layout = new QVBoxLayout;
QHBoxLayout * subLayout = new QHBoxLayout;
subLayout->addWidget(m_soundComboBox);
subLayout->addWidget(button);

layout->addLayout(subLayout);

m_preview->setLayout(layout);



}





