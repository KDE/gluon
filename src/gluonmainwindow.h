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
    KGLView * view(){return m_view;}
//   KCLVirtualInput * inputs(){return m_inputs;}
    void setView(KGLView * view ){
    m_view=view;
    }

public slots:
    void showKglService(){launchService("kgl.desktop");}
    void showKalService(){launchService("kal.desktop");}
    void showKclSercice(){launchService("kcl.desktop");}
    void showControlWidget();
    void showFps(int fps);
    void toggleFullscreen(bool);
protected:
    void setupGluon();
    void launchService(QString name);

private:
    KGLView * m_view;
    QList<QObject*> m_visibleWidgets;
   // KCLVirtualInput * m_inputs;


};
