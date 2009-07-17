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
   
    timer->setInterval (10);
      label = new QLabel(this);
      button = new QPushButton("press any button", this);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(button);
    
     connect(timer,SIGNAL(timeout()), this, SLOT(mainLoop()));
       connect(button,SIGNAL(clicked()), timer, SLOT(start()));
     
    setLayout(layout);
    
  }


void MyWidget::mainLoop()
{
  
if (!kclEngine->button().isNull())
{
  button->setText(kclEngine->button());
  button->setDown(false);
 timer->stop();
}

else button->setDown(true);

  
}