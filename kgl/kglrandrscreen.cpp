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


QList< KGLResolution > KGLRandRScreen::availableResolutions() const
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

  KGLScreen::applySettings();
}

int KGLRandRScreen::colourDepth() const
{
  return XDefaultDepth(m_display, m_screenID);
}

void KGLRandRScreen::retrieveResolutions()
{
  int numSizes = 0;
  XRRScreenSize* sizes = XRRSizes(m_display, m_screenID, &numSizes);
  for(int s = 0; s < numSizes; ++s)
  {
    int numRates;
    short* rates = XRRRates(m_display, m_screenID, s, &numRates);

    for(int r = 0; r < numRates; ++r)
    {
      KGLResolution newResolution(s, sizes[s].width, sizes[s].height, rates[r]);
      m_availableResolutions.append(newResolution);
    }
  }
}

int KGLRandRScreen::sizeID()
{
  foreach(const KGLResolution &res, m_availableResolutions)
  {
    if(res.width() == m_width && res.height() == m_height && res.refreshRate() == m_refreshRate) return res.id();
  }
  return -1;
}
