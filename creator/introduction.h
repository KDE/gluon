#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include "mainwindow.h"
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <QObject>
#include <QString>
class QDeclarativeContext;
class QDeclarativeView;
class QString;

class IntroSlideShow : public QObject{

public:
    IntroSlideShow(QObject *parent = 0);
    Q_INVOKABLE void updateDocker(QString dockername);
    void startIntro();
    MainWindow window;
    QDeclarativeView* view;
    QDeclarativeContext *context;
    QString docker;
};

#endif // IntroSlideShow_H
