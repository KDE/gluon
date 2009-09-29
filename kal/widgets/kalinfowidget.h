#ifndef KALINFOWIDGET_H
#define KALINFOWIDGET_H

#include "../kalengine.h"

#include <QComboBox>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QSlider>
#include <QWidget>

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
    KALInfoWidgetPrivate * d;
    QWidget *m_information;
    QWidget *m_preview;
    QComboBox *m_soundComboBox;

    KALSound *m_source;
};

#endif // KALINFOWIDGET_H
