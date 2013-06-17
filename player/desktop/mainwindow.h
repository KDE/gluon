#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <KXmlGuiWindow>
#include <KTextEdit>
#include <kdeclarative.h>
 
class MainWindow : public KXmlGuiWindow
{
  public:
    MainWindow(QWidget *parent=0);
 
  private:
	//variables
    KDeclarative kdeclarative;
    QDeclarativeView *qml_view;
    //methods
    void setupActions();
    void createQmlView();
};
 
#endif
