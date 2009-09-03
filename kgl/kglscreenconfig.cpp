#include "kglscreenconfig.h"
#include <QX11Info>
KGLScreenConfig::KGLScreenConfig(QObject * parent)
    :QObject(parent)
{
    dpy    = QX11Info::display();

    root   = RootWindow(dpy, 0);
 saveCurrentResolution();
}
KGLScreenConfig::~KGLScreenConfig()
{
restore();
}
QStringList KGLScreenConfig::resolutionAvaible()
{
    xrrs   = XRRSizes(dpy, 0, &num_sizes);
    QStringList resolutions;
    for(int i = 0; i < num_sizes; i ++) {
        short   *rates;
        int     num_rates;
        resolutions<<QString::number(xrrs[i].width) + "x" + QString::number(xrrs[i].height);
         rates = XRRRates(dpy, 0, i, &num_rates);

        for(int j = 0; j < num_rates; j ++) {
                possible_frequencies[i][j] = rates[j];
            }
    }
    return resolutions;
}

void KGLScreenConfig::saveCurrentResolution()
{
    conf                   = XRRGetScreenInfo(dpy, root);
    original_rate          = XRRConfigCurrentRate(conf);
    original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);
}
void KGLScreenConfig::restore()
{
    XRRSetScreenConfigAndRate(dpy, conf, root, original_size_id, original_rotation, original_rate, CurrentTime);
}
void KGLScreenConfig::setResolution(int id)
{
    if ( id > resolutionAvaible().size())
    {
        kDebug()<<"Resolution ID unvaible...";
        return;
    }
    XRRSetScreenConfigAndRate(dpy, conf, root, id, RR_Rotate_0, possible_frequencies[id][0], CurrentTime);
}
int KGLScreenConfig::askResolution()
{

KDialog * dialog = new KDialog;
QComboBox * combo = new QComboBox;
combo->addItems(resolutionAvaible());

   dialog->setCaption( "choose a resolution" );
   dialog->setButtons( KDialog::Apply | KDialog::Cancel );
dialog->setMainWidget(combo);
 connect( dialog, SIGNAL( applyClicked() ), dialog, SLOT( accept()) );
if ( dialog->exec())
return combo->currentIndex();
else return -1;


}
