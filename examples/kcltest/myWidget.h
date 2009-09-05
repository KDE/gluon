#include <QWidget>
#include <gluon/kcl/kclinput.h>
#include <gluon/kcl/kclmouse.h>
#include <gluon/kcl/kcldetect.h>
#include <gluon/kcl/kclbuttonwidget.h>

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <KDebug>
#include <QPixmap>
class MyWidget : public QWidget
{
  Q_OBJECT
  public : 
    MyWidget( QWidget * parent=0);
    ~MyWidget(){kDebug()<<"Destroy..\n";}
//     void paintEvent(QPaintEvent * event);
  public slots:
    void mainLoop();
  private:
 
KCLInput * input ;
KCLDetect * detect;
    QTimer * timer;
    
    QPixmap * pix;
    
    QPoint pos;

};
