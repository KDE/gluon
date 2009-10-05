#ifndef KGLScreenConfig_H
#define KGLScreenConfig_H

#include <QObject>
#include <QStringList>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KDialog>
#include <KDebug>

#include "kglscreen.h"

extern "C"
{
#include <X11/Xlib.h>
#define INT8 _X11INT8
#define INT32 _X11INT32
#include <X11/Xproto.h>
#undef INT8
#undef INT32
#include <X11/extensions/Xrandr.h>
}

/**
* A KGLScreen implementation for the X Window Rotate and Resize extension.
* This extension is the "modern" way of dealing with resolution changes and
* as such is used for our mode setting code.
*
* @todo Use one output per KGLScreen. This needs to be done together with some
* modifications to KGLDisplay. This would allow setting resolution of individual
* outputs and thus not turning off secondary outputs. Or even allow us to use
* those additional outputs to display stuff...
*/
class KGLRandRScreen : public KGLScreen
{
  Q_OBJECT
  public:
    KGLRandRScreen(int screen = 0);
    ~KGLRandRScreen();

    int colourDepth() const;
    QList< KGLResolution* > availableResolutions() const;
    
  public slots:
    void applySettings();

  private:
    void retrieveResolutions();
    
    Display *m_display;
    Window m_root;
    XRRScreenConfiguration *m_xrrConf;
    short m_originalRate;
    Rotation m_originalRotation;
    SizeID m_originalSizeID;

    int sizeID();
    QList<KGLResolution*> m_availableResolutions;
};

#endif // KGLScreenConfig_H
