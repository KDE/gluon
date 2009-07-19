#include <QWidget>
#include <gluon/kcl/kclinput.h>
#include <gluon/kcl/kclmouse.h>
#include <gluon/kcl/kclengine.h>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
class MyWidget : public QWidget
{
  Q_OBJECT
  public : 
    MyWidget( QWidget * parent=0);
    void paintEvent(QPaintEvent * event);
  public slots:
    void mainLoop();
  private:
    KCLInput * input;
    KCLMouse * mouse;
    KCLEngine * kcl;
    QTimer * timer;
    
    QPixmap * pix;
    
    QPoint pos;

};
