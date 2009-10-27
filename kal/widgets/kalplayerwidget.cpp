#include "kalplayerwidget.h"
#include "../kalsound.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QToolButton>
#include <QtGui/QMenu>
#include <QtCore/QTimer>
#include <QtGui/QWidgetAction>
#include <QtGui/QSlider>

#ifdef Q_WS_X11
#include <KUrlRequester>
#endif

#include <QtCore/QDebug>

class KALPlayerWidgetPrivate
{
public :
#ifdef Q_WS_X11
KUrlRequester * requester;
#endif
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
#ifdef Q_WS_X11
    d->requester = new KUrlRequester(parent);
    d->requester->setFilter("*.ogg *.wav");
    d->requester->setPath("/usr/share/sounds/KDE-Sys-Log-In.ogg");
#endif


    QToolButton *bplay = new QToolButton;
    bplay->setIcon(QIcon("media-playback-start.png"));

    QToolButton *bstop = new QToolButton;
    bstop->setIcon(QIcon("media-playback-stop.png"));

    QToolButton *bpause = new QToolButton;
    bpause->setIcon(QIcon("media-playback-pause.png"));


    QToolButton *bvolume = new QToolButton;
    bvolume->setIcon(QIcon("player-volume.png"));

    d->bar = new QSlider(Qt::Horizontal);
    d->bar->setMinimum(0);
    d->bar->setMaximum(100);

    QMenu * volumeMenu = new QMenu("volume");
    d->slider = new QSlider(Qt::Vertical);
    d->slider->setMinimum(0);
    d->slider->setMaximum(100);
    d->slider->setValue(100);
    QWidgetAction * volumeAction = new QWidgetAction(volumeMenu);
    volumeMenu->setIcon(QIcon("player-volume.png"));
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
#ifdef Q_WS_X11
    bigLayout->addWidget(d->requester);
#endif
    bigLayout->addWidget(d->bar);
    bigLayout->addLayout(layout);
    bigLayout->addStretch();

    connect(d->bar,SIGNAL(actionTriggered(int)),this,SLOT(setTimePosition(int)));
    connect(d->statusTimer,SIGNAL(timeout()),this,SLOT(updateStatus()));
    connect(bplay, SIGNAL(clicked()), d->sound, SLOT(play()));
    connect(bstop, SIGNAL(clicked()), d->sound, SLOT(stop()));
    connect(bpause, SIGNAL(clicked()),d->sound, SLOT(pause()));
    connect(d->slider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
#ifdef Q_WS_X11
    connect(d->requester,SIGNAL(textChanged(QString)),this,SLOT(load(QString)));
#endif

    setWindowTitle("select a sound and play it");

    setLayout(bigLayout);
#ifdef Q_WS_X11
    d->sound->load(d->requester->text());
#endif
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

#include "kalplayerwidget.moc"
