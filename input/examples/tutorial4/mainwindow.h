#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QGridLayout>
#include <QAction>
#include <QStatusBar>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,  Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

private:
    void setupUi();
    void retranslateUi();

    void createActions();
    void createMenus();
    void createStatusBar();

private slots:
    void mAbout();
    void resetUi();

private:
    // UI layout related direct widgets with parents
    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QTextEdit *textEdit;

    QMenuBar *menuBar;
    QStatusBar *statusBar;

    // File menu related action declarations
    QAction *quitAct;

    // Help menu related action declarations
    QAction *aboutAct;
    QAction *aboutQtAct;

    // Menubar entries
    QMenu   *fileMenu;
    QMenu   *helpMenu;

};

#endif // MAINWINDOW_H
