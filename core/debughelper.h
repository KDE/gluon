/*
 * code by wysota - http://blog.wysota.eu.org/index.php/2009/11/17/little-debugging-helper/
 */

#ifndef GLUON_CORE_DEBUGHELPER_H
#define GLUON_CORE_DEBUGHELPER_H

#include <QtCore/QString>

#include "gluon_core_export.h"

//#ifndef QT_NO_DEBUG
#    define DEBUG_FUNC_NAME GluonCore::DbgHelper dbgHelper(Q_FUNC_INFO);
#    define DEBUG_BLOCK GluonCore::DbgHelper dbgHelper;
#    define DEBUG_TEXT(X) dbgHelper.addText(X);
//#else
//#    define DEBUG_FUNC_NAME
//#    define DEBUG_BLOCK
//#    define DEBUG_TEXT(X)
//#endif

#define NO_COLOR 1

namespace GluonCore
{
    class GLUON_CORE_EXPORT DbgHelper
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
}

#endif // GLUON_CORE_DEBUGHELPER_H
