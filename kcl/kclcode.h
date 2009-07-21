#ifndef KCLCODE_H
#define KCLCODE_H
#include <QString>
class KCLCode
{
public:
    static QString keyName(int code);
    static QString eventName(int code);
    static QString relativName(int code);
    static QString absoluName(int code);
};

#endif // KCLCODE_H
