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

#include <QDockWidget>
#include <QStackedLayout>
#include <QComboBox>

#include <KStandardAction>
#include <KActionCollection>
#include <KIcon>
#include <gluon/kgl/kglscreen.h>

#include "shaderwidget.h"
#include "greyscaleshaderwidget.h"
#include "mosaicshaderwidget.h"
#include "posterizeshaderwidget.h"


MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent)
{
  //Create an Engine. This class contains all items that will be shown in the view.
  // to add item, call : addItem(KGLItem *) or addItems(KGLItemList *)
  mEngine = new KGLEngine;
  
  //this is the view widget . It's a QGLWidget child. Call KGLView::setEngine(KGLEngine *) to attach the engine to the view.
  // YOu can set the engine directly from the constructor
  mView = new KGLView(mEngine);
  
  //Add a preview object, so we can actually see what is happening
  mItem = new KGLBoxItem(5,5);
  mItem->setPosition(-mItem->center());
  mItem->updateTransform();
  mItem->setTexture(KIcon("kde.png").pixmap(128,128));
  mItem->setZIndex(1);

  //Add a white background
  //Note that there should probably be a simple function to set the background color
  //in KGLView. But until then, just fake it by using a KGLBoxItem.
  KGLBoxItem* bg = new KGLBoxItem(200, 200);
  bg->setPosition(-bg->center());
  bg->updateTransform();
  bg->setColor(Qt::white);
  bg->setZIndex(0);
  
  //after all setup... We can add the item inside the engine.
  mEngine->addItem(mItem);
  mEngine->addItem(bg);
  
  mView->start(); //start the game main loop

  setCentralWidget(mView);

  KStandardAction::quit(this, SLOT(close()), actionCollection());
  KStandardAction::fullScreen(mView, SLOT(setFullscreen(bool)), mView, actionCollection());

  setupDock();

  setupGUI();
}

MainWindow::~MainWindow()
{
  delete mEngine;
  mEngine = 0;
}

void MainWindow::shaderChanged(int index)
{
  if(index != 0)
  {
    KGLProgram * program = dynamic_cast<ShaderWidget*>(mWidgetStack->currentWidget())->program();
    mItem->setShaderFx(program);
  }
  else
  {
    mItem->setShaderFx(0);
  }
}


void MainWindow::setupDock()
{
  QDockWidget* shaders = new QDockWidget();
  shaders->setObjectName("Shaders");
  shaders->setWindowTitle("Shaders");
  addDockWidget(Qt::LeftDockWidgetArea, shaders);
  
  QVBoxLayout* layout = new QVBoxLayout();
  QComboBox* shadersSelector = new QComboBox();
  shadersSelector->addItems(QStringList() << "<None>" << "Greyscale" << "Posterize" << "Mosaic");
  layout->addWidget(shadersSelector);

  mWidgetStack = new QStackedLayout();
  mWidgetStack->addWidget(resolutionBox());
  mWidgetStack->addWidget(new GreyscaleShaderWidget);
  mWidgetStack->addWidget(new PosterizeShaderWidget);
  mWidgetStack->addWidget(new MosaicShaderWidget);

  layout->addLayout(mWidgetStack);
  
  connect(shadersSelector, SIGNAL(currentIndexChanged(int)), mWidgetStack, SLOT(setCurrentIndex(int)));
  connect(shadersSelector, SIGNAL(currentIndexChanged(int)), SLOT(shaderChanged(int)));
  
  QWidget* p = new QWidget(shaders);
  shaders->setWidget(p);
  
  p->setLayout(layout);
}

QWidget* MainWindow::resolutionBox()
{
   QComboBox* box = new QComboBox();
//  QList<KGLScreen*> screens = mView->display()->allScreens();
//   int i = 0;
//   foreach(KGLScreen* screen, screens)
//   {
//     box->addItem(QString("%1").arg(i++));
//   }
   return box;
}

