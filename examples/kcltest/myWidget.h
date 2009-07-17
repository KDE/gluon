#include <QWidget>
#include <gluon/kcl/kclengine.h>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
class MyWidget : public QWidget
{
  Q_OBJECT
  public : 
    MyWidget( QWidget * parent=0);
  public slots:
    void mainLoop();
    
  private:
  KCLEngine * kclEngine;
  QPushButton * button;
  QLabel * label;
  QTimer * timer;
  
};
