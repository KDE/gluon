/*
 * code by wysota - http://blog.wysota.eu.org/index.php/2009/11/17/little-debugging-helper/
 */

#include "debughelper.h"
#ifdef DBGHELPER_USES_PRINTF
#include <stdio.h>
#else
#include <QtCore/QtDebug>
#endif
 
int DbgHelper::indent = 0;
int DbgHelper::colorIndex = 0;
 
 
static void DbgHelper_output(int color, int indent, const QString &prefix, const QString &funcName)
{
    QString text = QString(4*indent, ' ')+QString(prefix+funcName);
    
    if(color>=0)
    {
        text.prepend("\x1b[3"+QString::number(1+color)+"m");
        text.append("\x1b[39m");
    }
  
#ifndef DBGHELPER_USES_PRINTF
    qDebug() << text;
#else
    fprintf(stderr, "%s\n", qPrintable(text));
#endif
    }
 
DbgHelper::DbgHelper(const QString &t)
{
    txt = t;
    
#ifdef NO_COLOR
    myColor=-1;
#else
    myColor = colorIndex;
    colorIndex = (colorIndex+1) % 7;
#endif
    DbgHelper_output(myColor, indent, "BEGIN ", txt);
    
    ++indent;
}

void DbgHelper::addText(const QString &t)
{
    DbgHelper_output(myColor, indent, "", t);
/*    if(messages.isEmpty())
        messages += QString("%1%2").arg(QString(4*indent - 1, ' ')).arg(t);
    else
        messages += QString("\n%1%2").arg(QString(4*indent + 1, ' ')).arg(t);*/
}

DbgHelper::~DbgHelper()
{
    --indent;
    DbgHelper_output(myColor, indent, "END ", txt);
}
