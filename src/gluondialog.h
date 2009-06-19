#ifndef GLUONDIALOG_H
#define GLUONDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>
#include "kal/kalengine.h"

#include "kglconfig.h"
#include "kalconfig.h"
#include "kclconfig.h"
class GluonDialog : public QDialog
{
    Q_OBJECT
public:
    GluonDialog();
    void createIcons();
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

};

#endif // GLUONDIALOG_H
