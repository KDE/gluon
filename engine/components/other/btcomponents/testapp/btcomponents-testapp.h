#ifndef btcomponents_testapp_H
#define btcomponents_testapp_H

#include <QtCore/QObject>

class QUrl;
class btcomponentstestapp : public QObject
{
Q_OBJECT
public:
    btcomponentstestapp();
    virtual ~btcomponentstestapp();
    
    void run(QUrl gdlFile);
};

#endif // btcomponents_testapp_H
