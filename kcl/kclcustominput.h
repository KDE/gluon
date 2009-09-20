#ifndef KCLCUSTOMINPUT_H
#define KCLCUSTOMINPUT_H

#include "kcldetect.h"
#include "kclinput.h"

#include <QObject>
#include <QList>
#include <QMap>

class KCLCustomInput : public QObject
{
    Q_OBJECT
public:
    KCLCustomInput(QObject * parent=0);
    void addButton(QString name, KCLInput* input, int keyCode);
    void addButton(QString name);
    void remButton(QString name);

    public slots:
    void test(int a){kDebug()<<"hello";}
    void emitButtonPressed(int code);
    void emitButtonReleased(int code);


signals:
    void buttonPressed(QString name);
    void buttonReleased(QString name);



private:
    QMap <QString,QPair<KCLInput*,int> > m_buttons;




};




#endif // KCLCUSTOMINPUT_H
