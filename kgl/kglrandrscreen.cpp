#include "kglrandrscreen.h"
#include <QX11Info>
#include <QLabel>

KGLRandRScreen::KGLRandRScreen()
{
  m_display = QX11Info::display();
  m_root = QX11Info::appRootWindow();

  //Save original screen settings
  m_xrrConf = XRRGetScreenInfo(m_display, m_root);
  m_originalRate = XRRConfigCurrentRate(m_xrrConf);
  m_originalSizeID = XRRConfigCurrentConfiguration(m_xrrConf, &m_originalRotation);
}
KGLRandRScreen::~KGLRandRScreen()
{
  if(m_fullscreen)
  {
    //Restore original screen settings
  }
}


QList< KGLScreenSettings > KGLRandRScreen::availableResolutions() const
{
  return QList<KGLScreenSettings>();
}


void KGLRandRScreen::applySettings()
{
  
}


/*
QStringList KGLRandRScreen::resolutionAvaible()
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
}*/
/*
void KGLRandRScreen::saveCurrentResolution()
{
    conf                   =
    original_rate          = XRRConfigCurrentRate(conf);
    original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);
}*//*
void KGLRandRScreen::restore()
{
    XRRSetScreenConfigAndRate(dpy, conf, root, original_size_id, original_rotation, original_rate, CurrentTime);
}
void KGLRandRScreen::setResolution(int id)
{
    if ( id > resolutionAvaible().size())
    {
        kDebug()<<"Resolution ID unvaible...";
        return;
    }
    XRRSetScreenConfigAndRate(dpy, conf, root, id, RR_Rotate_0, possible_frequencies[id][0], CurrentTime);
}
int KGLRandRScreen::askResolution()
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
*/