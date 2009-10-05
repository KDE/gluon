#include "kclmain.h"

#include <QtOpenGL/qgl.h>
#include <QtGui/qapplication.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGLWidget * widget = new QGLWidget();
    widget->show();
    return app.exec();
}
