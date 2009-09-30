/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kglscreen.h"


KGLScreen::KGLScreen(int screen) :
  m_fullscreen(false),
  m_width(0),
  m_height(0),
  m_colourDepth(0),
  m_screenID(screen)
{

}

KGLScreen::~KGLScreen()
{

}

void KGLScreen::setColourDepth(int depth, bool apply)
{
  m_colourDepth = depth;
  if(apply) applySettings();
}

void KGLScreen::setDimensions(int width, int height, bool apply)
{
  m_width = width;
  m_height = height;
  if(apply) applySettings();
}

void KGLScreen::setRefreshRate(short rate, bool apply)
{
  m_refreshRate = rate;
  if(apply) applySettings();
}

void KGLScreen::setFullscreen(bool fullscreen, bool apply)
{
  m_goFullscreen = fullscreen;
  if(apply) applySettings();
}

void KGLScreen::restore()
{
  m_goFullscreen = false;
  applySettings();
}

void KGLScreen::setResolution(KGLResolution* resolution)
{
  setDimensions(resolution->width, resolution->height, false);
  setRefreshRate(resolution->refreshRate, false);
  setColourDepth(resolution->colourDepth, false);
  applySettings();
}



