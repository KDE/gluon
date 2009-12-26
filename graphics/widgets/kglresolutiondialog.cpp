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

#include "kglresolutiondialog.h"
#include <kgl/kglscreen.h>
#include <kgl/kgldisplay.h>
#include <QtGui/QComboBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

KGLResolutionDialog::KGLResolutionDialog(QWidget* parent): QDialog(parent)
{
  setWindowTitle(tr("Select fullscreen resolution"));
  m_resolutions = KGLDisplay::instance()->currentScreen()->availableResolutions();
    
  m_resolutionComboBox = new QComboBox();

  for(int i = 0; i < m_resolutions.size(); ++i)
  {
    m_resolutionComboBox->addItem(m_resolutions.at(i).name(), i);
  }

  QWidget *widget = new QWidget(this);
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(new QLabel(tr("Please select your preferred fullscreen resolution:")));
  layout->addWidget(m_resolutionComboBox);
  widget->setLayout(layout);
  
  //setMainWidget(widget);
/*#ifdef Q_WS_X11
  setButtons(Ok | Cancel);
#endif*/
}

KGLResolution KGLResolutionDialog::selectedResolution() const
{
  return m_resolutions.at(m_resolutionComboBox->currentIndex());
}

#include "kglresolutiondialog.moc"
