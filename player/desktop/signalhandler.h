#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <QObject>
#include <QDebug>
 
class SignalHandler : public QObject
{
  Q_OBJECT
  
  public slots:
    void ping();
};
 
#endif
