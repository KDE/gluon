#include "kglrandrscreen.h"
#include <QX11Info>
#include <QLabel>

KGLRandRScreen::KGLRandRScreen(int screen) : KGLScreen(screen)
{
  m_display = QX11Info::display();
  m_root = QX11Info::appRootWindow(screen);

  m_xrrConf = XRRGetScreenInfo(m_display, m_root);
  //Save original screen settings
  m_originalRate = XRRConfigCurrentRate(m_xrrConf);
  m_originalSizeID = XRRConfigCurrentConfiguration(m_xrrConf, &m_originalRotation);

  retrieveResolutions();
}

KGLRandRScreen::~KGLRandRScreen()
{
  restore();
  XRRFreeScreenConfigInfo(m_xrrConf);
}


QList< KGLResolution* > KGLRandRScreen::availableResolutions() const
{
  return m_availableResolutions;
}


void KGLRandRScreen::applySettings()
{
  if(m_fullscreen && !m_goFullscreen)
  {
    XRRSetScreenConfigAndRate(m_display, m_xrrConf, m_root, m_originalSizeID, m_originalRotation, m_originalRate, CurrentTime);
    m_fullscreen = false;
    m_goFullscreen = false;
  }
  else if(!m_fullscreen && m_goFullscreen)
  {
    XRRSetScreenConfigAndRate(m_display, m_xrrConf, m_root, sizeID(), m_originalRotation, m_refreshRate, CurrentTime);
    m_fullscreen = true;
    m_goFullscreen = true;
  }

  emit screenSettingsChanged();
}

void KGLRandRScreen::retrieveResolutions()
{
  int numDepths = 0;
  int* depths = XListDepths(m_display, m_screenID, &numDepths);
  
  int numSizes = 0;
  XRRScreenSize* sizes = XRRSizes(m_display, m_screenID, &numSizes);
  for(int s = 0; s < numSizes; ++s)
  {
    int numRates;
    short* rates = XRRRates(m_display, m_screenID, s, &numRates);

    for(int r = 0; r < numRates; ++r)
    {
      for(int d = 0; d < numDepths; ++d)
      {
        KGLResolution* newResolution = new KGLResolution;
        newResolution->id = s;
        newResolution->width = sizes[s].width;
        newResolution->height = sizes[s].height;
        newResolution->refreshRate = rates[r];
        newResolution->colourDepth = depths[d];
        newResolution->name = QString("%1x%2@%3hz/%4bpp")
                                      .arg(newResolution->width)
                                      .arg(newResolution->height)
                                      .arg(newResolution->refreshRate)
                                      .arg(newResolution->colourDepth);
        m_availableResolutions.append(newResolution);
      }
    }
  }
  XFree(depths);
}

int KGLRandRScreen::sizeID()
{
  foreach(KGLResolution* res, m_availableResolutions)
  {
    if(res->width == m_width && res->height == m_height && res->refreshRate == m_refreshRate && res->colourDepth == m_colourDepth) return res->id;
  }
  return -1;
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