#ifndef KCLVIRTUALINPUT_H
#define KCLVIRTUALINPUT_H

#include <QObject>
#include <QList>
#include <QMap>
#include "kcldetect.h"
#include "kclinput.h"

class VirtualButton // create a virtal button : example VirtalButton("JUMP", KEY_UP, keyboard);
{
public:
    VirtualButton(QString name=0, int buttonCode=0, KCLInput *input=NULL);
    QString name(){return m_name;}
    int code(){return m_buttonCode;}
    KCLInput * input(){return m_input;}
    void setName(const QString& name){m_name = name;}
    void setButtonCode(int code){m_buttonCode =code;}
    void setInput(KCLInput * input){m_input = input;}
private:
    QString m_name;
    int m_buttonCode;
    KCLInput * m_input;
};


class KCLVirtualInput : public QObject
{
public:
    KCLVirtualInput(QObject * parent=0);
    void setButton(QString name);
    QList<VirtualButton*>primaryButtonList(){return m_primaryButtonList;}
    QList<VirtualButton*>secondaryButtonList(){return m_secondaryButtonList;}

private:
    QList <VirtualButton*> m_primaryButtonList;
    QList <VirtualButton*> m_secondaryButtonList;


};


#endif // KCLVIRTUALINPUT_H
