#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QObject>
#include <QGraphicsObject>
#include <KXmlGuiWindow>
#include <KTextEdit>
#include <kdeclarative.h>

#include "signalhandler.h"
 
class MainWindow : public KXmlGuiWindow
{
  public:
    MainWindow(QWidget *parent=0);
 
  private:
	//variables
    KDeclarative kdeclarative;
    QDeclarativeView *qml_view;
    QGraphicsObject *rootObject;
    SignalHandler signalHandler;
    //methods
    void setupActions();
    void createQmlView();
};
 
#endif
