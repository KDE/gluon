#ifndef SLIDEPUSHBUTTON_H
#define SLIDEPUSHBUTTON_H

#include <KPushButton>

class SlidePushButton : public KPushButton
{
    Q_OBJECT

public:
    SlidePushButton(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

public slots:
    void setRange(int min, int max) {
        m_min = min;
        m_max = max;
        if (min > max) {
            m_min = max;
            m_max = min;
        }
        update();
    }

    void setValue(int value) {
        if (value < m_min) m_value = m_min;
        if (value > m_max) m_value = m_max;
        m_value = value;
        update();
    }

private:
    int m_min;
    int m_max;
    int m_value;
};

#endif // SLIDEPUSHBUTTON_H
