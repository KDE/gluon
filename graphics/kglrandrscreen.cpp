#include "kglrandrscreen.h"
#include <QX11Info>
#include <QLabel>

extern "C"
{
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/extensions/Xrandr.h>
}

class KGLRandRScreenPrivate
{
  public:
    Display *m_display;
    Window m_root;
    XRRScreenConfiguration *m_xrrConf;
    short m_originalRate;
    Rotation m_originalRotation;
    SizeID m_originalSizeID;
    QList<KGLResolution> m_availableResolutions;
};

KGLRandRScreen::KGLRandRScreen(int screen) : KGLScreen(screen)
{
  d = new KGLRandRScreenPrivate();
  d->m_display = QX11Info::display();
  d->m_root = QX11Info::appRootWindow(screen);

  d->m_xrrConf = XRRGetScreenInfo(d->m_display, d->m_root);
  //Save original screen settings
  d->m_originalRate = XRRConfigCurrentRate(d->m_xrrConf);
  d->m_originalSizeID = XRRConfigCurrentConfiguration(d->m_xrrConf, &d->m_originalRotation);

  retrieveResolutions();
}

KGLRandRScreen::~KGLRandRScreen()
{
  restore();
  XRRFreeScreenConfigInfo(d->m_xrrConf);
  delete d;
}


QList< KGLResolution > KGLRandRScreen::availableResolutions() const
{
  return d->m_availableResolutions;
}


void KGLRandRScreen::applySettings()
{
  if(m_fullscreen && !m_goFullscreen)
  {
    XRRSetScreenConfigAndRate(d->m_display, d->m_xrrConf, d->m_root, d->m_originalSizeID, d->m_originalRotation, d->m_originalRate, CurrentTime);
    m_fullscreen = false;
    m_goFullscreen = false;
  }
  else if(!m_fullscreen && m_goFullscreen)
  {
    XRRSetScreenConfigAndRate(d->m_display, d->m_xrrConf, d->m_root, sizeID(), d->m_originalRotation, m_refreshRate, CurrentTime);
    m_fullscreen = true;
    m_goFullscreen = true;
  }

  KGLScreen::applySettings();
}

int KGLRandRScreen::colourDepth() const
{
  return XDefaultDepth(d->m_display, m_screenID);
}

void KGLRandRScreen::retrieveResolutions()
{
  int numSizes = 0;
  XRRScreenSize* sizes = XRRSizes(d->m_display, m_screenID, &numSizes);
  for(int s = 0; s < numSizes; ++s)
  {
    int numRates;
    short* rates = XRRRates(d->m_display, m_screenID, s, &numRates);

    for(int r = 0; r < numRates; ++r)
    {
      KGLResolution newResolution(s, sizes[s].width, sizes[s].height, rates[r]);
      d->m_availableResolutions.append(newResolution);
    }
  }
}

int KGLRandRScreen::sizeID()
{
  foreach(const KGLResolution &res, d->m_availableResolutions)
  {
    if(res.width() == m_width && res.height() == m_height && res.refreshRate() == m_refreshRate) return res.id();
  }
  return -1;
}

#include "kglrandrscreen.moc"
