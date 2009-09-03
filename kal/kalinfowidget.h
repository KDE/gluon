#ifndef KALINFOWIDGET_H
#define KALINFOWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QComboBox>
#include <QSlider>
class KALInfoWidget : public QWidget
{
public:
    KALInfoWidget(QWidget * parent=0);
void setupComboBox();
void setupPreview();
    private:
    QWidget *m_information;
    QWidget *m_preview;
    QComboBox * m_soundComboBox;
};

#endif // KALINFOWIDGET_H
