

#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    GluonPlayer::MainWindow window(argc, argv);
    window.show();

    return app.exec();
}
