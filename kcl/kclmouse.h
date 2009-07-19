#ifndef KCLMOUSE_H
#define KCLMOUSE_H
#include "kclinput.h"
#include <QPoint>
#include <QList>
#include <QWidget>
class KCLMouse : public KCLInput
{
    Q_OBJECT
public:
    KCLMouse(QString device,QObject * parent=0);
    QPoint position(){return relPos();  }

    private:
    QPoint m_position;
    QWidget *m_widget;

};

#endif // KCLMOUSE_H
