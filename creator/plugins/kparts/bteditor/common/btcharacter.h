#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include <smarts/lib/btlib_export.h>
#include <QDebug>

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
public:
    btCharacter();
    ~btCharacter();
    void stopThinking();
    void startThinking();
    void hello(){qDebug() << "btCharacter hello";}
    bool continueThinking();
private:
    bool think;
};

#endif // _BTCHARACTER_H_
