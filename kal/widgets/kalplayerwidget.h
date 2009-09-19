#ifndef KALPLAYERWIDGET_H
#define KALPLAYERWIDGET_H

#include "../kalsound.h"

#include <QWidget>
#include <QSlider>
#include <KUrlRequester>

class KALPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    KALPlayerWidget(QWidget * parent = 0);

public slots:
    void load(const QString& file);
    void setVolume(int v);
private:
    KUrlRequester * requester;
    KALSound * sound;
    QSlider * slider;
};

#endif // KALPLAYERWIDGET_H
