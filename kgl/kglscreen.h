
template<class T1, class T2 >
struct QPair;/*
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

#ifndef KGLSCREENCONFIG_H
#define KGLSCREENCONFIG_H

#include <QtCore/QObject>
#include <QtCore/QList>

/**
* A simple data structure to hold information
* about a screen resolution.
*/
struct KGLResolution
{
  QString name;
  int id;
  int width;
  int height;
  short refreshRate;
};

/**
* This class describes the interface for screen configurations.
* It should be subclassed for specific window systems and im-
* plementations.
*
*/
class KGLScreen : public QObject
{
  Q_OBJECT
  public:
    KGLScreen(int screen = 0);
    virtual ~KGLScreen();

    virtual int width() const { return m_width; }
    virtual int height() const { return m_height; }
    virtual int colourDepth() const = 0;
    virtual short refreshRate() const { return m_refreshRate; }
    virtual bool isFullscreen() const { return m_fullscreen; }
    virtual int screenID() const { return m_screenID; }
    virtual QList<KGLResolution*> availableResolutions() const = 0;
    
  public slots:
    virtual void setDimensions(int width, int height, bool apply = true);
    virtual void setRefreshRate(short int rate, bool apply = true);
    virtual void setFullscreen(bool fullscreen, bool apply = true);
    virtual void setResolution(KGLResolution* resolution);
    
    virtual void restore();
    virtual void applySettings() = 0;

  signals:
    void screenSettingsChanged();

  protected:
    /**
    * @todo Move this into a KGLScreenPrivate class
    */
    bool  m_fullscreen;
    bool  m_goFullscreen;
    int   m_width;
    int   m_height;
    short m_refreshRate;

    int   m_screenID;
};

#endif // KGLSCREENCONFIG_H
