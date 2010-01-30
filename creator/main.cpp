#include "mainwindow.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

int main(int argc, char **argv)
{
    KAboutData aboutData("gluoncreator", NULL,
                        ki18n("Gluon Creator"), "1.0",
                        ki18n("A tool to easily create games"),
                        KAboutData::License_GPL,
                        ki18n("Copyright (c) 2009 The Gluon Developers"),
                        KLocalizedString(),
                        "http://gluon.tuxfamily.org"
                         );
    aboutData.setProgramIconName("gluon");
    aboutData.addAuthor(ki18n("Arjen Hiemstra"), KLocalizedString(), "djfreestyler@gmail.com" );
    aboutData.addAuthor(ki18n("Dan Leinir Tuthra Jensen"), KLocalizedString(), "");

    KCmdLineArgs::init(argc, argv, &aboutData);
    KCmdLineOptions options;
    options.add("+file", ki18n("GDL file to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;

    GluonCreator::MainWindow* window = new GluonCreator::MainWindow;
    window->show();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if (args->count())
    {
        window->openProject(args->arg(0));
    }

    app.exec();
}
