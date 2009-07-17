#include <QWidget>
#include <gluon/kcl/kclengine.h>
#include <QTimer>
#include <QLabel>
class MyWidget : public QWidget
{
  Q_OBJECT
  public : 
    MyWidget( QWidget * parent=0);
  public slots:
    void mainLoop();
    
  private:
  KCLEngine * kclEngine;
  QLabel * label;
  QTimer * timer;
  
};
