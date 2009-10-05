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
