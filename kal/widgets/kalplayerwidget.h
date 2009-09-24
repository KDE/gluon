#ifndef KALPLAYERWIDGET_H
#define KALPLAYERWIDGET_H

#include "../kalsound.h"

#include <QWidget>
#include <QSlider>
#include <KUrlRequester>
#include <QTimer>
class KALPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    KALPlayerWidget(QWidget * parent = 0);

public slots:
    void load(const QString& file);
    void setVolume(int v);
    void setTimePosition(int t);
    void updateStatus();

private:
    KUrlRequester * requester;
    KALSound * sound;
    QSlider * slider;
    QTimer * statusTimer;
    QSlider * bar;
};

#endif // KALPLAYERWIDGET_H
