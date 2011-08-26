#include <QtGui/QApplication>
#include "bteditor.h"
#include <QResource>

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>

int main(int argc, char** argv)
{

    KAboutData aboutData( "gluon_bteditor", "gluon_bteditor",
        ki18n("Behavior Tree Editor"), "0.1",
        ki18n("A MainWindow for Behavior Tree Editor"),
        KAboutData::License_GPL,
        ki18n("Copyright (c) 2007 Developer") );
    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options;
    options.add("+[file]", ki18n("Document to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;
    bteditor *foo=new bteditor();
    foo->show();
    return app.exec();
}
