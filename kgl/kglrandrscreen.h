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
 * \defgroup KGL KGL
 */
//@{

class KGLRandRScreen : public KGLScreen
{
  Q_OBJECT
  public:
    KGLRandRScreen();
    ~KGLRandRScreen();

    QList< KGLScreenSettings > availableResolutions() const;
    
  public slots:
    void applySettings();
    
  private:
    Display *m_display;
    Window m_root;
    int m_numSizes;
    XRRScreenSize *m_xrrSize;
    XRRScreenConfiguration *m_xrrConf;
    short m_possibleFrequencies[64][64];
    short m_originalRate;
    Rotation m_originalRotation;
    SizeID m_originalSizeID;
};

//@}
#endif // KGLScreenConfig_H
