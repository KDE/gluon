

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include "mainwindow.h"

int main(int argc, char **argv) {
    KAboutData aboutData("gluoncreator", NULL,
                        ki18n("Gluon Creator"), "1.0",
                        ki18n("Gluon Creator"),
                        KAboutData::License_GPL,
                        ki18n("Copyright (c) 2009 Developer"));
                        KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;

    Gluon::Creator::MainWindow* main = new Gluon::Creator::MainWindow;
    main->show();

    app.exec();
}
