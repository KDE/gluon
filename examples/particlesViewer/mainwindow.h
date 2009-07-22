#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QMainWindow>
#include <QDockWidget>
#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglengine.h>
#include <gluon/kgl/kglparticlesitem.h>

#include "optionwidget.h"
class MainWindow : public QMainWindow
{
  Q_OBJECT
  public : 
    MainWindow( QWidget * parent=0);

  public slots:
  void start();

private:
    
    KGLView * m_view;
    KGLEngine * m_engine;

    KGLParticlesItem * particles;

OptionWidget * optionWidget;

};

#endif
