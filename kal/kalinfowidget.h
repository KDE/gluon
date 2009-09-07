#ifndef KALINFOWIDGET_H
#define KALINFOWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QComboBox>
#include <QGraphicsPixmapItem>
#include <QSlider>
#include "kalengine.h"
class KALInfoWidget : public QWidget
{
    Q_OBJECT
public:
    KALInfoWidget(QWidget * parent=0);
    void setupComboBox();
    void setupPreview();
    void setupInformation();

public slots:

    void setDevice(const QString& device);

private:
    QWidget *m_information;
    QWidget *m_preview;
    QComboBox * m_soundComboBox;

    KALSound * m_source;

};

#endif // KALINFOWIDGET_H
