/*
 * code by wysota - http://blog.wysota.eu.org/index.php/2009/11/17/little-debugging-helper/
 */

#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include <QtCore/QString>

#ifndef QT_NO_DEBUG
#    define DEBUG_FUNC_NAME DbgHelper dbgHelper(Q_FUNC_INFO);
#    define DEBUG_BLOCK DbgHelper dbgHelper;
#    define DEBUG_TEXT(X) dbgHelper.addText(X);
#else
#    define DEBUG_FUNC_NAME
#    define DEBUG_BLOCK
#    define DEBUG_TEXT(X)
#endif

#define NO_COLOR 1
 
class DbgHelper
{
    public:
        DbgHelper();
        DbgHelper(const QString &t);
        ~DbgHelper();
        
        void addText(const QString &t);
    private:
        QString txt;
        static int indent;
        static int colorIndex;
        int myColor;
        bool noFunctionName;
};
#endif
