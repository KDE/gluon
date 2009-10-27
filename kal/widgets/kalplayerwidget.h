#ifndef KALPLAYERWIDGET_H
#define KALPLAYERWIDGET_H

#include "../kal_export.h"

#include <QtGui/QWidget>

class KALPlayerWidgetPrivate;
class KAL_EXPORT KALPlayerWidget : public QWidget
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
    Q_DISABLE_COPY(KALPlayerWidget)
    
    KALPlayerWidgetPrivate *d;
};

#endif // KALPLAYERWIDGET_H
