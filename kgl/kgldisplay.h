/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KGLDISPLAY_H
#define KGLDISPLAY_H

#include <QtCore/QObject>
#include <QCoreApplication>

#include "kgl_export.h"

class KGLScreen;

/**
* @class KGLDisplay
*
* This class is a container class for screen objects. It creates all the necessary screen objects
* to manage the actual screens on the system.
*
* @todo Think of a way to create screens independent of operating system. Maybe use a factory?
*/
class KGL_EXPORT KGLDisplay : public QObject
{
  Q_OBJECT
  public:
    /**
    * The currently active screen.
    */
    virtual KGLScreen* currentScreen() const;
    /**
    * A list of all screens.
    */
    virtual QList<KGLScreen*> allScreens() const;

    static KGLDisplay* instance()
    {
      if(!m_instance)
      {
        m_instance = new KGLDisplay(QCoreApplication::instance());
      }
      return m_instance;
    }

  protected:
    KGLDisplay(QObject* parent = 0);
    virtual ~KGLDisplay();
    
    QList<KGLScreen*> m_screens;

    static KGLDisplay* m_instance;
    
};

#endif // KGLDISPLAY_H
