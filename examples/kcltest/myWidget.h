#include <QWidget>
#include <gluon/kcl/kclinput.h>

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
class MyWidget : public QWidget
{
  Q_OBJECT
  public : 
    MyWidget( QWidget * parent=0);
  public slots:
    void mainLoop();
  private:
    KCLInput * input;
    QTimer * timer;
};
