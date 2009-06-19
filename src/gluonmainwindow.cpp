#include "gluonmainwindow.h"
#include <KConfigDialog>
#include <KLocale>

GluonMainWindow::GluonMainWindow(QWidget * parent)
  :KXmlGuiWindow(parent)
{

m_view = new KGLView();

setCentralWidget(m_view);
setupGUI();

}


