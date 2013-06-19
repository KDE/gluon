#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QObject>
#include <QDebug>
 
class LoginForm : public QObject
{
  Q_OBJECT
  
  public slots:
    Q_INVOKABLE void ping();
};
 
#endif
