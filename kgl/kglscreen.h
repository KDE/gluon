
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

struct KGLScreenSettings
{
  int width;
  int height;
  int colourDepth;
  int refreshRate;
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
    KGLScreen();
    virtual ~KGLScreen();

    /*virtual KGLScreenInfo* screen(int screenIndex) const;
    virtual int screenCount() const;
    virtual QList<const KGLScreenInfo*> allScreens() const;*/

    virtual int width() const { return m_width; }
    virtual int height() const { return m_height; }
    virtual int colourDepth() const { return m_colourDepth; }
    virtual float refreshRate() const { return m_refreshRate; }
    virtual bool isFullscreen() const { return m_fullscreen; }
    virtual QList<KGLScreenSettings> availableResolutions() const = 0;
    
  public slots:
    virtual void setDimensions(int width, int height, bool apply = true);
    virtual void setColourDepth(int depth, bool apply = true);
    virtual void setFullscreen(bool fullscreen, bool apply = true);
    virtual void applySettings() = 0;

  signals:
    void screenSettingsChanged();

  protected:
    /*KGLScreenInfo m_currentScreenSettings;
    int           m_screenCount;
    QList<KGLScreenInfo*> m_screens;*/
    bool  m_fullscreen;
    int   m_width;
    int   m_height;
    int   m_colourDepth;
    float m_refreshRate;
};

#endif // KGLSCREENCONFIG_H
