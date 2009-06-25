#include "gluonmainwindow.h"
#include <KConfigDialog>
#include <KLocale>

GluonMainWindow::GluonMainWindow(QWidget * parent)
  :KXmlGuiWindow(parent)
{


m_gl  = new KGLEngine();
m_al  = new KALEngine();
m_view = new KGLView(m_gl);
setCentralWidget(m_view);
setupGUI();

}

GluonMainWindow::~GluonMainWindow()
{
   delete m_al;
}
