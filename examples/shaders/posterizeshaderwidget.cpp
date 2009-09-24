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

#include "posterizeshaderwidget.h"
#include <QFormLayout>
#include <QSlider>
#include <gluon/kgl/kglprogram.h>
#include <QLabel>

PosterizeShaderWidget::PosterizeShaderWidget(QWidget* parent): ShaderWidget(parent)
{
  mProgram = new KGLProgram();
  mProgram->addShader(new KGLFragmentShader("posterize.frag"));
  mProgram->setUniform("tex", 0);
  mProgram->setUniform("level", 20.0f);
  mProgram->link();

  QFormLayout* layout = new QFormLayout;
  QSlider* slider = new QSlider;
  slider->setMaximum(20);
  slider->setMinimum(1);
  slider->setSliderPosition(20);
  slider->setOrientation(Qt::Horizontal);
  connect(slider, SIGNAL(valueChanged(int)), SLOT(sliderChanged(int)));

  layout->addWidget(new QLabel("Posterize Filter Settings"));
  layout->addWidget(new QLabel("Levels"));
  layout->addWidget(slider);

  setLayout(layout);
}

void PosterizeShaderWidget::sliderChanged(int value)
{
  mProgram->setUniform("level", float(value));
}
