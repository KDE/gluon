#include "introduction.h"
#include <QRect>
class QRect;

IntroSlideShow::IntroSlideShow(QObject *parent) :
    QObject(parent){

  startIntro();
}


void IntroSlideShow::startIntro(){

    view = new QDeclarativeView( window );
    context = view->rootContext();
    context->setContextProperty("intro", this);
    view->setSource( QUrl::fromLocalFile( KGlobal::dirs()->locate( "appdata", "introduction.qml" ) ));
    view->setStyleSheet("background: transparent");
    view->setResizeMode( QDeclarativeView::SizeRootObjectToView );
    view->setGeometry( window->rect());
    view->show();

}

void IntroSlideShow::updateDocker(QString dockername){

    docker =dockername;
    QObject *object = view->rootObject();
    QObject *geometry = object->findChild<QObject*>("geometry");
    if(geometry){
        QRect rectangle= new QRect();
        rectangle= window->findChild<QWidget*>( docker )->frameGeometry();
        geometry->setProperty("width",rectangle.width());
        geometry->setProperty("x",rectangle.x());
        geometry->setProperty("y",rectangle.y());
        geometry->setProperty("height",rectangle.height());
    }

}
