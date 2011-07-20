#include <QtCore/QCoreApplication>
#include "btcomponents-testapp.h"
#include <QUrl>
#include <QStringList>
#include <QDebug>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    
    QUrl theURL;
    if(QCoreApplication::arguments().count() == 1)
        theURL = QUrl("./test.gdl");
    else
        theURL = QUrl(QCoreApplication::arguments().at(1));
    
    btcomponentstestapp foo;
    foo.run(theURL);
    
    app.quit();

    return app.exec();
}
