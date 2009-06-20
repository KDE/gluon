#ifndef KALCONFIG_H
#define KALCONFIG_H

#include <QWidget>
#include <QTabWidget>
#include "kal/kalengine.h"
#include "kal/kalsource.h"
#include <AL/al.h>
class KALConfig : public QWidget
{
    Q_OBJECT
public:
    KALConfig();
    ~KALConfig(){delete m_alEngine;}
void setupInformation();
void setupTest();
public slots:
void play();
    private:
        KALEngine *m_alEngine;
   QTabWidget * m_tab;
   KALSource * m_source;
};

#endif // KALCONFIG_H
