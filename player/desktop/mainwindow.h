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

#include <player/lib/serviceprovider.h>
#include <attica/providermanager.h>
#include <attica/provider.h>


class MainWindow : public KXmlGuiWindow
{
	public:
		MainWindow(QWidget *parent=0);
		
	public slots:
		void loadQml(QString filename);
		void initDone();
		void initFailed();
		
	private:
		//variables
		KDeclarative kdeclarative;
		QDeclarativeView *qml_view;
		QGraphicsObject *rootObject;
		//methods
		void setupActions();
		void createQmlView();
		void initAttica();
};

#endif

