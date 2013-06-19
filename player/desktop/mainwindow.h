#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QObject>
#include <QGraphicsObject>
#include <KXmlGuiWindow>
#include <KTextEdit>
#include <kdeclarative.h>

#include "loginform.h"
 
class MainWindow : public KXmlGuiWindow
{
  public:
    MainWindow(QWidget *parent=0);
 
  private:
	//variables
    KDeclarative kdeclarative;
    QDeclarativeView *qml_view;
    QGraphicsObject *rootObject;
    //methods
    void setupActions();
    void createQmlView();
};
 
#endif
