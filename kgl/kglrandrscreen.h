#ifndef KGLScreenConfig_H
#define KGLScreenConfig_H


#include "kglscreen.h"

class KGLRandRScreenPrivate;

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
    QList< KGLResolution > availableResolutions() const;
    
  public slots:
    void applySettings();

  private:
    Q_DISABLE_COPY(KGLRandRScreen)
    void retrieveResolutions();
    int sizeID();
    
    KGLRandRScreenPrivate *d;
};

#endif // KGLScreenConfig_H
