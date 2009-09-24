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

#include "mainwindow.h"
#include <KStandardAction>
#include <kactioncollection.h>

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent)
{
  //Create an Engine. This class contains all items that will be shown in the view.
  // to add item, call : addItem(KGLItem *) or addItems(KGLItemList *)
  mEngine = new KGLEngine;
  
  //this is the view widget . It's a QGLWidget child. Call KGLView::setEngine(KGLEngine *) to attach the engine to the view.
  // YOu can set the engine directly from the constructor
  mView = new KGLView(mEngine);
  
  // This function show the current axis xy
  mView->setAxisShow(false);
  mView->setInfoShow(true);
  
  KGLBoxItem * item = new KGLBoxItem(5,5);
  item->setPosition(-item->itemCenter());
  item->updateTransform();
  item->setColor(Qt::red);
  item->setTexture(KIcon("kde.png").pixmap(128,128));
  
  mMosaic = new KGLProgram();
  KGLFragmentShader* mosaicFrag = new KGLFragmentShader(QString("mosaic.frag"));
  mMosaic->addShader(mosaicFrag);
  mMosaic->setUniform("tex", 1);
  mMosaic->setUniform("texSize", (int)item->texture()->dim().width());
  mMosaic->setUniform("amount", 1);
  mMosaic->link();
  
  if(!mMosaic->isValid())
  {
    kWarning() << "Invalid fragment program, aborting fragment program use.";
    kWarning() << "Compile log: " << mosaicFrag->compileLog();
    kWarning() << "Link log: " << mMosaic->linkLog();
  }
  else
  {
    item->setProgram(mMosaic);
  }
  
  //after all setup... We can add the item inside the engine.
  mEngine->addItem(item);

  QSlider* slider = new QSlider();
  slider->setMinimum(1);
  slider->setMaximum(128);
  slider->setSingleStep(0.1f);
  slider->setOrientation(Qt::Horizontal);
  connect(slider, SIGNAL(valueChanged(int)), SLOT(mosaicAmount(int)));
  
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(slider);
  layout->addWidget(mView);
  
  mView->start(); //start the game main loop

  QWidget* central = new QWidget();
  setCentralWidget(central);
  central->setLayout(layout);

  KStandardAction::quit(this, SLOT(close()), actionCollection());

  setupGUI();
}

MainWindow::~MainWindow()
{
  delete mEngine;
  mEngine = 0;
}


void MainWindow::mosaicAmount(int amt)
{
  mMosaic->setUniform("amount", amt);
}
