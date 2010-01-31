#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <gluon/graphics/glwidget.h>
#include <gluon/graphics/engine.h>
#include <gluon/graphics/item.h>
#include <gluon/graphics/texture.h>
#include <gluon/graphics/widgetproxy.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  GluonGraphics::Engine * engine = new GluonGraphics::Engine;
  GluonGraphics::GLWidget * widget = new GluonGraphics::GLWidget;
  widget->setEngine(engine);

  GluonGraphics::Item * box = new GluonGraphics::Item;
  box->createBox(200,200);

  box->setTexture("/usr/share/icons/oxygen/64x64/apps/akonadi.png");
  box->showBoundingBox(true);
  box->showCenter(true);

  engine->addItem(box);



  GluonGraphics::WidgetProxy* proxy = new GluonGraphics::WidgetProxy(widget);
  QWidget* embeddedWindow = proxy->createWindow("Window title");
  embeddedWindow->move(10, 10); 

  proxy->addWidget(embeddedWindow);   
  proxy->show();

  widget->toggleShowFps();

  return app.exec();

}
