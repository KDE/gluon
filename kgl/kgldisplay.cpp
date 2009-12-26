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

#include "kgldisplay.h"

#ifdef Q_WS_X11
#include "kglrandrscreen.h"
#include <X11/Xlib.h>
#include <QX11Info>
#endif

//template<> KGLDisplay* KSingleton<KGLDisplay>::m_instance = 0;

KGLDisplay::KGLDisplay()
{
#ifdef Q_WS_X11
  int screens = XScreenCount(QX11Info::display());
  for(int i = 0; i < screens; ++i)
  {
    m_screens.append(new KGLRandRScreen(i));
  }
#endif
}

KGLDisplay::~KGLDisplay()
{
  qDeleteAll(m_screens);
  m_screens.clear();
}

QList< KGLScreen* > KGLDisplay::allScreens() const
{
  return m_screens;
}


KGLScreen* KGLDisplay::currentScreen() const
{
  return m_screens.at(0);
}

#include "kgldisplay.moc"
