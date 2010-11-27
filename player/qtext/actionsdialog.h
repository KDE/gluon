#ifndef ACTIONSDIALOG_H
#define ACTIONSDIALOG_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVariant>
#include <QApplication>
#include <QButtonGroup>
#include <QList>
#include <QAction>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QStringList>
#include <QPushButton>
#include <QSettings>
#include <QScopedPointer>
#include <QDebug>

namespace Ui {
    class ActionsDialog;
}

class ActionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionsDialog(QList<QAction *> actions,
                  QWidget *parent = 0);
    virtual ~ActionsDialog();

protected:
    void changeEvent(QEvent *e);

protected slots:
    void accept();

private slots:
    void recordAction(int curr_row, int curr_col, int prev_row,
                      int prev_col);
    void validateAction(int row, int col);
    void mSaveShortcuts();
    void buttonBoxClicked(QAbstractButton *optionsDialogPushButton);

private:
    void setupUi();
    void retranslateUi();
    void setFallbacksEnabled(bool enabled);

    QString oldAccelText;
    QList<QAction *> actionsList;
    QScopedPointer<QSettings> settings;
    QList<QAction *> m_actions;

    // UI layout related direct widgets with parents
    QGridLayout *gridLayout;
    QTableWidget *TableWidgetActions;
    QDialogButtonBox *buttonBox;
};

#endif // ACTIONSDIALOG_H
