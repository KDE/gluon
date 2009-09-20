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
    void addAbsAxis(QString name, KCLInput * input, int axis);
    void addRelAxis(QString name,KCLInput* input, int axis);
    void remAbsAxis(QString name);
    void remRelAxis(QString name);



signals:
    void buttonPressed(QString name);
    void buttonReleased(QString name);
    void absAxisChanged(QString name,int value);
    void relAxisChanged(QString name,int value);
    void absAxisChanged(QString name);
    void relAxisChanged(QString name);

protected slots:
    void emitButtonPressed(int code);
    void emitButtonReleased(int code);
   void emitAbsAxisChanged(int axis, int value);
   void emitRelAxisChanged(int axis, int value);

private:
    QMap <QString,QPair<KCLInput*,int> > m_buttons;
    QMap <QString,QPair<KCLInput*,int> > m_absAxis;
    QMap <QString,QPair<KCLInput*,int> > m_relAxis;


};




#endif // KCLCUSTOMINPUT_H
