#include <QtGui/QApplication>
#include "bteditor.h"
#include <QResource>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    bteditor foo;
    foo.show();
    return app.exec();
}
