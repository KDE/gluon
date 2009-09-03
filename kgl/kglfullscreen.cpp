#include "kglscreenconfig.h"

KGLScreenConfig::KGLScreenConfig(QObject * parent)
        :QObject(parent)
{


}

    QStringList KGLScreenConfig::resolutionAvaible()
    {

    xrrs   = XRRSizes(QX11Info::display(), 0, &num_sizes);
QStringList resolutions;
    for(int i = 0; i < num_sizes; i ++) {
        short   *rates;
        int     num_rates;
        resolutions<<QString::number(xrrs[i].width) + "x" + QString::number(xrrs[i].height);
    }
return resolutions;
    }



    void KGLScreenConfig::saveCurrentResolution()
{
//    XRRScreenConfiguration  *conf;
//    Window                  root;
//    SizeID                  original_size_id;
//    Rotation                original_rotation;
//    root   = RootWindow(QX11Info::display(), 0);
//    conf                   = XRRGetScreenInfo(QX11Info::display(), root);
//    original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);
//    m_originalResolution = original_size_id;
}

