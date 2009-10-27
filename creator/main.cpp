#include "mainwindow.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

int main(int argc, char **argv)
{
    KAboutData aboutData("gluoncreator", NULL,
                        ki18n("Gluon Creator"), "1.0",
                        ki18n("Gluon Creator"),
                        KAboutData::License_GPL,
                        ki18n("Copyright (c) 2009 Developer"));
    aboutData.setProgramIconName("gluon");

    KCmdLineArgs::init(argc, argv, &aboutData);
    KCmdLineOptions options;
    options.add("+file", ki18n("GDL file to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;

    Gluon::Creator::MainWindow* window = new Gluon::Creator::MainWindow;
    window->show();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if (args->count())
    {
        window->openProject(args->arg(0));
    }

    app.exec();
}
