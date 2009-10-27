#ifndef KALINFOWIDGET_H
#define KALINFOWIDGET_H

#include "../kal_export.h"

#include <QtGui/QWidget>

class KALInfoWidgetPrivate;
class KAL_EXPORT KALInfoWidget : public QWidget
{
    Q_OBJECT

public:
    KALInfoWidget(QWidget * parent = 0);
    void setupComboBox();
    void setupPreview();
    void setupInformation();

public slots:
    void setDevice(const QString& device);

private:
    Q_DISABLE_COPY(KALInfoWidget)
    KALInfoWidgetPrivate * d;
};

#endif // KALINFOWIDGET_H
