#include "kgl/kglview.h"
#include "kal/kalengine.h"

#include <QMainWindow>
#include <KXmlGuiWindow>
class GluonMainWindow: public KXmlGuiWindow
{
public:
GluonMainWindow(QWidget * parent=0);
~GluonMainWindow();
KGLView * view(){return m_view;}
KALEngine *alEngine(){return m_al;}
KGLEngine *glEngine(){return m_gl;}

void setEngine(KGLEngine * engine){m_gl = engine;m_view->setEngine(engine);}


private:
KGLView * m_view;
KGLEngine * m_gl;
KALEngine * m_al;

};
