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
#include <kglview.h>
#include <kglscreen.h>
#include <QComboBox>
#include <QVBoxLayout>
#include <klocalizedstring.h>
#include <QLabel>

KGLResolutionDialog::KGLResolutionDialog(QWidget* parent): KDialog(parent)
{
  setCaption(i18n("Select fullscreen resolution"));
  m_resolutions = KGLDisplay::instance()->currentScreen()->availableResolutions();
    
  m_resolutionComboBox = new QComboBox();

  for(int i = 0; i < m_resolutions.size(); ++i)
  {
    m_resolutionComboBox->addItem(m_resolutions.at(i)->name, i);
  }
  

  connect(this, SIGNAL(accepted()), SLOT(saveSettings()));

  QWidget *widget = new QWidget(this);
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(new QLabel(i18n("Please select your preferred fullscreen resolution:")));
  layout->addWidget(m_resolutionComboBox);
  widget->setLayout(layout);
  
  setMainWidget(widget);
  setButtons(Ok | Cancel);
}

void KGLResolutionDialog::saveSettings()
{
  m_selectedResolution = m_resolutions.at(m_resolutionComboBox->currentIndex());
}


