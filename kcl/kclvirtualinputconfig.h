#ifndef KCLVIRTUALINPUTCONFIG_H
#define KCLVIRTUALINPUTCONFIG_H

#include <QWidget>
#include <QTreeWidget>
#include <KDialog>
#include <KLineEdit>
#include "kcldetect.h"
#include "kclvirtualinput.h"
#include "kclbutton.h"
class KCLVirtualInputConfig : public KDialog
{
    Q_OBJECT
public:
    KCLVirtualInputConfig(KCLVirtualInput * input ,QWidget * parent=0);


public slots:
    void setup();
private slots:
    void changeButton(QTreeWidgetItem * item, int column);
private:
    QTreeWidget * m_treeWidget;
    KCLVirtualInput * m_virtualInput;

};

#endif // KCLVIRTUALINPUTCONFIG_H
