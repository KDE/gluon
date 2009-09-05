#include "kgl/kglview.h"
#include "kal/kalengine.h"
#include <QMainWindow>
#include <KXmlGuiWindow>
#include <KActionCollection>

#include <KAction>
class GluonMainWindow: public KXmlGuiWindow
{
    Q_OBJECT
public:
GluonMainWindow(QWidget * parent=0);
~GluonMainWindow();
void setGLEngine(KGLEngine * engine){m_view->setEngine(engine);}


public slots:
void showKglService(){launchService("kgl.desktop");}
void showKalService(){launchService("kal.desktop");}
void showKclSercice(){launchService("kcl.desktop");}

protected:
void setupAction();
void launchService(QString name);


private:
KGLView * m_view;


};
