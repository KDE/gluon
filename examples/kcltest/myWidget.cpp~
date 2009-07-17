#include "myWidget.h"
#include <KDebug>
#include <QVBoxLayout>
MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
  {
     setMouseTracking(true);
    kclEngine = new KCLEngine(this);
   
    installEventFilter(kclEngine);
    
    
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(mainLoop()));
    timer->start(10);
      label = new QLabel(this);
      
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(label);
  
    setLayout(layout);
    
  }


void MyWidget::mainLoop()
{
  

  
  label->setText(kclEngine->getButton());
  
}