#ifndef KCLCUSTOMINPUT_H
#define KCLCUSTOMINPUT_H

#include "kcldetect.h"
#include "kclinput.h"

#include <QObject>
#include <QList>
#include <QMap>

class KCL_EXPORT KCLCustomInput : public QObject
{
    Q_OBJECT
public:
    KCLCustomInput(QObject * parent=0);
    void setButton(const QString &name, KCLInput* input, int keyCode);
    void setButton(const QString &name);
    void remButton(const QString &name);
    void setAbsAxis(const QString &name, KCLInput * input, int axis);
    void setRelAxis(const QString &name,KCLInput* input, int axis);
    void remAbsAxis(const QString &name);
    void remRelAxis(const QString &name);



    QStringList buttonNameList();
    QStringList absAxisNameList();
    QStringList relAxisNameList();


    KCLInput * inputAt(const QString& name, KCL::InputTypeFlag type);
   int codeAt(const QString& name, KCL::InputTypeFlag type);

    QStringList buttonNameList();
    QStringList absAxisNameList();
    QStringList relAxisNameList();


    KCLInput * inputAt(const QString& name, KCL::InputTypeFlag type);
   int codeAt(const QString& name, KCL::InputTypeFlag type);

    bool button(const QString& name);
    int relAxisValue(const QString &name);
    int absAxisValue(const QString &name);


signals:
    void buttonPressed(QString name);
    void buttonReleased(QString name);
    void absAxisChanged(QString name,int value);
    void relAxisChanged(QString name,int value);

protected slots:
     void inputEvent(KCLInputEvent * event);


private:
    QMap <QString,QPair<KCLInput*,int> > m_buttons;
    QMap <QString,QPair<KCLInput*,int> > m_absAxis;
    QMap <QString,QPair<KCLInput*,int> > m_relAxis;


};




#endif // KCLCUSTOMINPUT_H
