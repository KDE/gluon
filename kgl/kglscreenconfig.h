#ifndef KGLScreenConfig_H
#define KGLScreenConfig_H

#include <QObject>
#include <QStringList>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KDialog>
#include <KDebug>

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






class KGLScreenConfig : public QObject
{
    Q_OBJECT
public:
    KGLScreenConfig(QObject * parent=0);
~KGLScreenConfig();

int askResolution();
public slots:
    void setResolution(int id);
    void restore();
   QStringList resolutionAvaible();
protected:
    void saveCurrentResolution();
   private:
    Display                 *dpy;

Window                  root;
int                     num_sizes;
XRRScreenSize           *xrrs;
XRRScreenConfiguration  *conf;
short                   possible_frequencies[64][64];
short                   original_rate;
Rotation                original_rotation;
SizeID                  original_size_id;


};

#endif // KGLScreenConfig_H
