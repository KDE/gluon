#ifndef KALPLAYERWIDGET_H
#define KALPLAYERWIDGET_H

#include "kalsound.h"

#include <QWidget>

#include <KUrlComboRequester>

class KALPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    KALPlayerWidget(QWidget * parent = 0);

public slots:
    void play();

private:
    KUrlRequester * requester;
    KALSound * sound;
};

#endif // KALPLAYERWIDGET_H
