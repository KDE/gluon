#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputeventtextedit.h"

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QGridLayout>
#include <QAction>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = 0,  Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    InputEventTextEdit *inputEventTextEdit();

private:
    void setupUi();
    void retranslateUi();

    void createActions();
    void createMenus();
    void createStatusBar();

    void changeEvent(QEvent *event);

private slots:
    void mAbout();

private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;
    InputEventTextEdit *m_inputEventTextEdit;

    QMenuBar *menuBar;
    QStatusBar *statusBar;

    QAction *quitAct;

    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu   *fileMenu;
    QMenu   *helpMenu;
};

#endif // MAINWINDOW_H
