/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "gdlhandler.h"
#include <QStringList>

using namespace Gluon;

GDLHandler &
GDLHandler::instance()
{
    static GDLHandler theInstance;
    return theInstance;
}

QObject *
GDLHandler::instantiateObject(QString className)
{
    QObject * newObject = 0;
    
    if(className == "")
    {
    }
    else
        newObject = new QObject();
    
    return newObject;
}

QList<QStringList>
GDLHandler::tokenizeObject(QString objectString)
{
    QList<QStringList> tokenizedObject;
    
    bool inItem = false;
    bool inName = false;
    bool inValue = false;
    bool inChild = false;
    bool beingEscaped = false;
    int extraBracketCounter = 0;
    QString currentString;
    QStringList currentItem;
    
    QString::const_iterator i;
    for(i = objectString.begin(); i != objectString.end(); ++i)
    {
        if(inItem)
        {
            if(!inValue && !inName && !inChild)
            {
                if(!currentString.isEmpty())
                {
                    currentItem.append(currentString.trimmed());
                    currentString.clear();
                }
                
                // Ignore whitespace as instructed, rar!
                if(!i->isSpace())
                {
                    if(i->toLower() == '}')
                    {
                        // Once we hit an end, we should stop looking at this item
                        // In other words - add the item to the list of items and make a new stringlist to work on...
                        QStringList theItem(currentItem);
                        tokenizedObject.append(theItem);
                        currentItem.clear();
                    }
                    else if(i->toLower() == '{')
                    {
                        // If we hit a start while already inside an item, we should simply start adding stuff
                        // until we hit the correct ending again
                        inChild = true;
                    }
                    else
                    {
                        // Once you hit something, start reading the name
                        inName = true;
                    }
                }
            }
            
            if(inChild)
            {
                if(i->toLower() == '\\' && !beingEscaped)
                    beingEscaped = true;
                else
                {
                    currentString += i->unicode();
                    if(!beingEscaped)
                    {
                        if(i->toLower() == '{')
                        {
                            ++extraBracketCounter;
                        }
                        if(i->toLower() == '}')
                        {
                            --extraBracketCounter;
                            if(extraBracketCounter == -1)
                            {
                                // Now we're ready to look for more values, yay! ;)
                                extraBracketCounter = 0;
                                inChild = false;
                            }
                        }
                    }
                    else
                        beingEscaped = false;
                }
            }
            else if(inName)
            {
                // Read name until we hit a space, and after that, start reading the value...
                if(!i->isSpace())
                {
                    currentString += i->unicode();
                }
                else
                {
                    inName = false;
                    inValue = true;
                }
            }
            else if(inValue)
            {
                if(i->toLower() == '\\' && !beingEscaped)
                    beingEscaped = true;
                else
                {
                    // Read the value until the value ends, wooh! ;)
                    currentString += i->unicode();
                    if(!beingEscaped && i->toLower() == ')')
                    {
                        inValue = false;
                    }
                    beingEscaped = false;
                }
            }
        }
        else
        {
            if(i->isSpace())
            {
                // Just do nothing - whitespace should be ignored outside of items
            }
            else
            {
                if(i->toLower() == '{')
                {
                    inItem = true;
                }
            }
        }
    }
    
    return tokenizedObject;
}

QList<QObject *>
GDLHandler::parseGDL(const QString parseThis, QObject * parent)
{
    QList<QObject *> thisObject;
    
    QList<QStringList> tokenizedObject = tokenizeObject(parseThis);
    foreach(const QStringList &item, tokenizedObject)
    {
        
    }
    
    return thisObject;
}

QString
serializeGDL(QObject * serializeThis)
{
    QString serializedData;
    return serializedData;
}
