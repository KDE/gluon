#include "kalinfowidget.h"
#include <KTitleWidget>
#include <QVBoxLayout>
#include <KTabWidget>
#include <KIcon>
#include <QDir>
#include <KPushButton>
#include <QLabel>
#include <QMessageBox>
#include <KLocale>
KALInfoWidget::KALInfoWidget(QWidget * parent)
        :QWidget(parent)
{

    KALEngine::getInstance();
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


m_scene = new QGraphicsScene(0,0,100,100);
QGraphicsView * view = new QGraphicsView(m_scene);

m_scene->addLine(m_scene->sceneRect().center().x(),m_scene->sceneRect().top(),m_scene->sceneRect().center().x(),m_scene->sceneRect().bottom());
m_scene->addLine(m_scene->sceneRect().left(),m_scene->sceneRect().center().y(),m_scene->sceneRect().right(),m_scene->sceneRect().center().y());
m_scene->addText(i18n("Move the audio icon arround the center to test 3d sound"))->setPos(m_scene->sceneRect().topLeft());
QGraphicsPixmapItem * user= new QGraphicsPixmapItem(KIcon("im-user").pixmap(32,32));
user->setPos(m_scene->sceneRect().center() - user->boundingRect().center());
user->setZValue(1);
m_scene->addItem(user);


m_item = new QGraphicsPixmapItem(KIcon("speaker.png").pixmap(32,32));
m_item->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
m_item->setZValue(2);
m_scene->addItem(m_item);

KPushButton * button = new KPushButton(KIcon("media-playback-start.png"),"play");
QVBoxLayout * layout = new QVBoxLayout;
QHBoxLayout * subLayout = new QHBoxLayout;
layout->addWidget(view);
subLayout->addWidget(m_soundComboBox);
subLayout->addStretch();
subLayout->addWidget(button);
layout->addLayout(subLayout);
m_preview->setLayout(layout);
connect(button,SIGNAL(clicked()),this,SLOT(playSound()));
}
void KALInfoWidget::setupInformation()
{
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
QVBoxLayout * lv = new QVBoxLayout;
lv->addWidget(logo);
lv->addWidget(label);
m_information->setLayout(lv);

}

void KALInfoWidget::playSound()
{


QString path("/usr/share/sounds/");
m_source =new KALSource(path+m_soundComboBox->currentText());
QPointF position = m_item->pos() - m_scene->sceneRect().center() + m_item->boundingRect().center();
position = position *0.1;

//
//
QMessageBox::information(0,"test",QString::number(position.x()) + QString("--") + QString::number(position.y()));
m_source->setPosition(m_item->x(), m_item->y(),0);
m_source->play();


}


