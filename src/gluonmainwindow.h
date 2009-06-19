#include "kgl/kglview.h"
#include "kal/kalengine.h"

#include <QMainWindow>
#include <KXmlGuiWindow>
class GluonMainWindow: public KXmlGuiWindow
{
public:
GluonMainWindow(QWidget * parent=0);
void configureSettings();

private:
KGLView * m_view;

};
