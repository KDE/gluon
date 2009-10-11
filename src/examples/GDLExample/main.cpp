

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include "mainwindow.h"

int main(int argc, char **argv) {
    KAboutData aboutData("gdlexample", NULL,
                        ki18n("GDL Example"), "1.0",
                        ki18n("GDL Example"),
                        KAboutData::License_GPL,
                        ki18n("Copyright (c) 2009 Developer"));
                        KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;

    MainWindow* main = new MainWindow;
    main->show();

    app.exec();
}
