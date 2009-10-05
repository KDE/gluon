
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
* @class KGLSCreen
*
* This class describes the interface for screen configurations.
* Specific subclasses of this class should implement the behaviour and
* functionality for different operating systems.
*
* Only the pure virtual methods are necessary to be implemented, together
* with a constructor. All the other methods make use of the data of those
* methods.
*
* @see KGLRandRScreen
*/
class KGLScreen : public QObject
{
  Q_OBJECT
  public:
    /**
    * Constructor.
    * @param screen The screen number this object is created for.
    */
    KGLScreen(int screen = 0, QObject* parent = 0);
    
    virtual ~KGLScreen();

    /**
    * The width of the screen.
    */    
    virtual int width() const { return m_width; }
    /**
    * The height of the screen.
    */
    virtual int height() const { return m_height; }
    /**
    * The screen colour depth.
    * @note While we do not allow setting colour depth, retrieving it can be
    * useful sometimes.
    */
    virtual int colourDepth() const = 0;
    /**
    * The refresh rate of the screen.
    */
    virtual short refreshRate() const { return m_refreshRate; }
    /**
    * Is this screen in fullscreen mode?
    */
    virtual bool isFullscreen() const { return m_fullscreen; }
    /**
    * The ID (number) of the screen.
    */
    virtual int screenID() const { return m_screenID; }
    /**
    * Return all resolutions this screen can be set to.
    */
    virtual QList<KGLResolution*> availableResolutions() const = 0;
    
  public slots:
    /**
    * Set the width and height of the screen.
    * @note Note that it is not guaranteed to work with arbitrary screen sizes. If you want
    * to be certain, use #availableResolutions to retrieve all available resolutions and use
    * one of those resolutions.
    * @param width The width of the screen
    * @param height The height of the screen
    * @param apply Immediately apply these changes or delay them. If these changes are delayed,
    * a call to #applySettings will apply the changes.
    */    
    virtual void setDimensions(int width, int height, bool apply = true);
    /**
    * Set the refresh rate of the screen.
    * @see #setDimensions
    */
    virtual void setRefreshRate(short int rate, bool apply = true);
    /**
    * Set fullscreen mode.
    * @see #setDimensions
    */
    virtual void setFullscreen(bool fullscreen, bool apply = true);
    /**
    * Set all screen properties from one Resolution object.
    * @note This also applies those properties.
    */
    virtual void setResolution(KGLResolution* resolution);
    /**
    * Restore the screen to its original settings. This method should be called
    * when switching from fullscreen back to a normal resolution.
    */
    virtual void restore();
    /**
    * Apply all pending changes.
    * It will emit a screenSettingsChanged signal after the screen settings have been changed.
    */
    virtual void applySettings();

  signals:
    /**
    * Emitted when the screen settings have been changed.
    */
    void screenSettingsChanged();

  protected:
    bool  m_fullscreen;
    bool  m_goFullscreen;
    int   m_width;
    int   m_height;
    short m_refreshRate;

    int   m_screenID;
};

#endif // KGLSCREENCONFIG_H
