#include "kalplayerwidget.h"
#include "../kalsound.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QToolButton>
#include <QMenu>
#include <QWidgetAction>
#include <KUrlRequester>
#include <KDebug>

class KALPlayerWidgetPrivate
{
public :
KUrlRequester * requester;
KALSound * sound;
QSlider * slider;
QTimer * statusTimer;
QSlider * bar;
};

KALPlayerWidget::KALPlayerWidget(QWidget *parent)
    : QWidget(parent),
    d(new KALPlayerWidgetPrivate)
{
    d->statusTimer = new QTimer;
    d->statusTimer->setInterval(1000);
    d->statusTimer->start();
    d->sound = new KALSound;
    QHBoxLayout *layout = new QHBoxLayout;

    d->requester = new KUrlRequester(parent);
    d->requester->setFilter("*.ogg *.wav");
    d->requester->setPath("/usr/share/sounds/KDE-Sys-Log-In.ogg");


    QToolButton *bplay = new QToolButton;
    bplay->setIcon(KIcon("media-playback-start.png"));

    QToolButton *bstop = new QToolButton;
    bstop->setIcon(KIcon("media-playback-stop.png"));

    QToolButton *bpause = new QToolButton;
    bpause->setIcon(KIcon("media-playback-pause.png"));


    QToolButton *bvolume = new QToolButton;
    bvolume->setIcon(KIcon("player-volume.png"));

    d->bar = new QSlider(Qt::Horizontal);
    d->bar->setMinimum(0);
    d->bar->setMaximum(100);

    QMenu * volumeMenu = new QMenu("volume");
    d->slider = new QSlider(Qt::Vertical);
    d->slider->setMinimum(0);
    d->slider->setMaximum(100);
    d->slider->setValue(100);
    QWidgetAction * volumeAction = new QWidgetAction(volumeMenu);
    volumeMenu->setIcon(KIcon("player-volume.png"));
    volumeAction->setDefaultWidget(d->slider);
    volumeMenu->addAction(volumeAction);
    bvolume->setMenu(volumeMenu);
    bvolume->setPopupMode(QToolButton::InstantPopup);


    QVBoxLayout * bigLayout = new QVBoxLayout;
    layout->addWidget(bplay);
    layout->addWidget(bpause);
    layout->addWidget(bstop);
    layout->addStretch();
    layout->addWidget(bvolume);

    bigLayout->addWidget(d->requester);
    bigLayout->addWidget(d->bar);
    bigLayout->addLayout(layout);
    bigLayout->addStretch();

    connect(d->bar,SIGNAL(actionTriggered(int)),this,SLOT(setTimePosition(int)));
    connect(d->statusTimer,SIGNAL(timeout()),this,SLOT(updateStatus()));
    connect(bplay, SIGNAL(clicked()), d->sound, SLOT(play()));
    connect(bstop, SIGNAL(clicked()), d->sound, SLOT(stop()));
    connect(bpause, SIGNAL(clicked()),d->sound, SLOT(pause()));
    connect(d->slider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
    connect(d->requester,SIGNAL(textChanged(QString)),this,SLOT(load(QString)));

    setWindowTitle("select a sound and play it");

    setLayout(bigLayout);
    d->sound->load(d->requester->text());
}

void KALPlayerWidget::load(const QString &file)
{   
    d->sound->stop();
    d->sound->load(file);
    d->sound->setVolume(float(d->slider->value())/100);
}
void KALPlayerWidget::setVolume(int v)
{
    d->sound->setVolume(float(v)/100);

}
void KALPlayerWidget::updateStatus()
{
    if ( d->sound->status() == AL_PLAYING)
        d->bar->setValue(d->sound->elapsedTime()*100/d->sound->duration());


}
void KALPlayerWidget::setTimePosition(int t)
{
    if ( d->sound->status() == AL_PLAYING)
    {
        d->sound->stop();
        float tps = d->bar->value()*d->sound->duration()/100;
        d->sound->setTimePosition(tps);
        d->sound->play();
    }
}
void KALPlayerWidget::updateStatus()
{
    if ( sound->status() == AL_PLAYING)
        bar->setValue(sound->elapsedTime()*100/sound->duration());


}
void KALPlayerWidget::setTimePosition(int t)
{
    if ( sound->status() == AL_PLAYING)
    {
        sound->stop();
        float tps = bar->value()*sound->duration()/100;
        sound->setTimePosition(tps);
        sound->play();
    }
}
