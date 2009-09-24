#include "kalplayerwidget.h"
#include "../kalsound.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QToolButton>
#include <QMenu>
#include <QWidgetAction>
#include <KUrlRequester>
#include <KDebug>
KALPlayerWidget::KALPlayerWidget(QWidget *parent)
    : QWidget(parent)
{
    statusTimer = new QTimer;
    statusTimer->setInterval(1000);
    statusTimer->start();
    sound = new KALSound;
    QHBoxLayout *layout = new QHBoxLayout;

    requester = new KUrlRequester(parent);
    requester->setFilter("*.ogg *.wav");
    requester->setPath("/usr/share/sounds/KDE-Sys-Log-In.ogg");


    QToolButton *bplay = new QToolButton;
    bplay->setIcon(KIcon("media-playback-start.png"));

    QToolButton *bstop = new QToolButton;
    bstop->setIcon(KIcon("media-playback-stop.png"));

    QToolButton *bpause = new QToolButton;
    bpause->setIcon(KIcon("media-playback-pause.png"));


    QToolButton *bvolume = new QToolButton;
    bvolume->setIcon(KIcon("player-volume.png"));

    bar = new QSlider(Qt::Horizontal);
    bar->setMinimum(0);
    bar->setMaximum(100);

    QMenu * volumeMenu = new QMenu("volume");
    slider = new QSlider(Qt::Vertical);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(100);
    QWidgetAction * volumeAction = new QWidgetAction(volumeMenu);
    volumeMenu->setIcon(KIcon("player-volume.png"));
    volumeAction->setDefaultWidget(slider);
    volumeMenu->addAction(volumeAction);
    bvolume->setMenu(volumeMenu);
    bvolume->setPopupMode(QToolButton::InstantPopup);


    QVBoxLayout * bigLayout = new QVBoxLayout;
    layout->addWidget(bplay);
    layout->addWidget(bpause);
    layout->addWidget(bstop);
    layout->addStretch();
    layout->addWidget(bvolume);


    bigLayout->addWidget(requester);
    bigLayout->addWidget(bar);
    bigLayout->addLayout(layout);
    bigLayout->addStretch();



    connect(bar,SIGNAL(actionTriggered(int)),this,SLOT(setTimePosition(int)));
    connect(statusTimer,SIGNAL(timeout()),this,SLOT(updateStatus()));
    connect(bplay, SIGNAL(clicked()), sound, SLOT(play()));
    connect(bstop, SIGNAL(clicked()), sound, SLOT(stop()));
    connect(bpause, SIGNAL(clicked()),sound, SLOT(pause()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
    connect(requester,SIGNAL(textChanged(QString)),this,SLOT(load(QString)));

    setWindowTitle("select a sound and play it");

    setLayout(bigLayout);
    sound->load(requester->text());
}

void KALPlayerWidget::load(const QString &file)
{   
    sound->stop();
    sound->load(file);
    sound->setVolume(float(slider->value())/100);


}
void KALPlayerWidget::setVolume(int v)
{
    sound->setVolume(float(v)/100);

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
