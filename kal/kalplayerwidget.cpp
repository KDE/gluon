#include "kalplayerwidget.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QMessageBox>
#include "kalsound.h"
KALPlayerWidget::KALPlayerWidget(QWidget * parent)
    :QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;

    requester = new KUrlRequester;
    requester->setFilter("*.ogg *.wav");
    requester->setPath("/usr/share/sounds/KDE-Sys-Log-In.ogg");
    QToolButton * bplay = new QToolButton;
    bplay->setIcon(KIcon("media-playback-start.png"));
    QToolButton * bstop = new QToolButton;
    bstop->setIcon(KIcon("media-playback-stop.png"));
    layout->addWidget(requester);
    layout->addWidget(bplay);
    layout->addWidget(bstop);
    sound = new KALSound("");
    connect(bplay,SIGNAL(clicked()),this,SLOT(play()));


    setWindowTitle("select a sound and play it");

    setLayout(layout);
}
void KALPlayerWidget::play()
{
    sound= new KALSound(requester->text());
    sound->play();
}
