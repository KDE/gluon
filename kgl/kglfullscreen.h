#ifndef KGLScreenConfig_H
#define KGLScreenConfig_H

#include <QObject>
#include <QStringList>
#include<X11/Xlib.h>
#include<X11/extensions/Xrandr.h>
#include <QX11Info>

/**
 * \defgroup KGL KGL
 */
//@{

class KGLScreenConfig : public QObject
{
public:
    KGLScreenConfig(QObject * parent=0);
    void saveCurrentResolution();
   QStringList resolutionAvaible();


   private:
Window                  root;
int                     num_sizes;
XRRScreenSize           *xrrs;
XRRScreenConfiguration  *conf;
short                   possible_frequencies[64][64];
short                   original_rate;
Rotation                original_rotation;
SizeID                  original_size_id;


};

//@}
#endif // KGLScreenConfig_H
