#include "mainwindow.h"
#include <KDebug>
#include <QVBoxLayout>
#include "optionwidget.h"
#include <KDebug>
MainWindow::MainWindow(QWidget *parent)
  :QMainWindow(parent)
  {

    m_engine = new KGLEngine;
m_view = new KGLView(m_engine);
    setCentralWidget(m_view);
    
    m_view->setAxisShow(true);
    m_view->setInfoShow(true);

    particles = new KGLParticlesItem;

optionWidget = new OptionWidget;


      QDockWidget *dockWidget = new QDockWidget(tr("option"), this);
     dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                 Qt::RightDockWidgetArea);
     dockWidget->setWidget(optionWidget);
     addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    
    
    connect(optionWidget->startButton,SIGNAL(clicked()),this, SLOT(start()));


    
  }


void MainWindow::start()
{

    delete particles;
     particles = new KGLParticlesItem;
    particles->clear();

    QString sprite = optionWidget->spriteRequester->text();

    int number = optionWidget->numberSpin->value();
    int angle = optionWidget->angleSpin->value();
   double speed = optionWidget->speedSpin->value();
    double alpha=  optionWidget->alphaSpin->value();
  int size = optionWidget->sizeSpin->value();


  if ( optionWidget->typeCheckBox-> isTristate ())
    particles->createExplose(number,QPixmap(sprite),angle,speed,alpha,size);

  else
      particles->createSmoke(number,QPixmap(sprite),angle,speed,alpha,size);


    m_engine->addItem(particles);
    m_view->start();





}
