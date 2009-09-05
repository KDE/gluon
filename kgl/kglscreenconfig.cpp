#include "kglscreenconfig.h"
#include <QX11Info>
#include <QLabel>
KGLScreenConfig::KGLScreenConfig(QObject * parent)
    :QObject(parent)
{
 dpy    = QX11Info::display();
 root   = QX11Info::appRootWindow();
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

dialog->setWindowIcon(KIcon("kgl.png"));
QComboBox * combo = new QComboBox;
combo->addItems(resolutionAvaible());
QLabel * icon = new QLabel;
icon->setPixmap(KIcon("video-display.png").pixmap(64,64));
dialog->setCaption( "choose a resolution" );
QHBoxLayout * layout = new QHBoxLayout;
layout->addWidget(icon);
layout->addWidget(combo);
QWidget * main = new QWidget;
main->setLayout(layout);
   dialog->setButtons( KDialog::Apply | KDialog::Cancel );
dialog->setMainWidget(main);
 connect( dialog, SIGNAL( applyClicked() ), dialog, SLOT( accept()) );
if ( dialog->exec())
return combo->currentIndex();
else return -1;


}
