

#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setOrganizationName("KDE Gluon");
    app.setApplicationName("Gluon Player");


    GluonPlayer::MainWindow window(argc, argv);
    window.show();

    return app.exec();
}
