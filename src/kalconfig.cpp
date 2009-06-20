#include "kalconfig.h"
#include <QVBoxLayout>
#include <QLabel>
#include <KDebug>
#include <QPushButton>
KALConfig::KALConfig()
{
m_alEngine = new KALEngine;
m_tab = new QTabWidget;
QVBoxLayout * layout = new QVBoxLayout;
layout->addWidget(m_tab);
setLayout(layout);
m_source = new KALSource("",m_alEngine);
setupInformation();
setupTest();

}
void KALConfig::setupInformation()
{

QLabel *label= new QLabel ;
QString info="";
info+="<p>Vendor :"+QString(alGetString(AL_VENDOR))+ "</p>";
info+="<p>Version :"+QString(alGetString(AL_VERSION)) + "</p>";
info+="<p>Renderer :"+QString(alGetString(AL_RENDERER)) + "</p>";

//info+="<p>Vendor :"+QString(alcGetString(m_alEngine->AL_DEFAULT_DEVICE_SPECIFIER))+ "</p>";
//info+="<p>Version :"+QString(alcGetString(AL_VERSION)) + "</p>";
//info+="<p>Renderer :"+QString(alcGetString(AL_RENDERER)) + "</p>";


label->setText(info);
QVBoxLayout * lv = new QVBoxLayout;
lv->addWidget(label);

QWidget * main = new QWidget;
main->setLayout(lv);
m_tab->addTab(main,"information");
}

void KALConfig::setupTest()
{


  QPushButton * button = new QPushButton("click to play a sound...");

  QWidget * main = new QWidget;
  QVBoxLayout * lv = new QVBoxLayout;
  lv->addWidget(button);
  main->setLayout(lv);
m_tab->addTab(main,"test");

connect(button,SIGNAL(clicked()),this, SLOT(play()));


}

void KALConfig::play()
{
   m_source->stop();
    m_source->play();

}
