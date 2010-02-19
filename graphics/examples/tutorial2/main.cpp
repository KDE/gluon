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

  GluonGraphics::GLWidget * widget = new GluonGraphics::GLWidget;
  GluonGraphics::Item * box = new GluonGraphics::Item;
  box->createBox(200,200);

  box->showBoundingBox(true);
  box->showCenter(true);

  GluonGraphics::WidgetProxy* proxy = new GluonGraphics::WidgetProxy(widget);
  QWidget* embeddedWindow = proxy->createWindow("Window title");
  embeddedWindow->move(10, 10); 

  proxy->addWidget(embeddedWindow);   
  proxy->show();

  widget->toggleShowFps();

  return app.exec();

}
