#ifndef BTNEWTREEWIZARD_H
#define BTNEWTREEWIZARD_H

#include <QWizard>

class QLabel;
class QLineEdit;
class btNodeEditWidget;


class NewTreeWizard : public QWizard
{
    Q_OBJECT

    public:
        NewTreeWizard(QWidget *parent = 0);
        void accept();
    Q_SIGNALS:
        void behaviorTreeCreated(QString name);
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class NamePage : public QWizardPage
{
    Q_OBJECT

public:
    NamePage(QWidget *parent = 0);

private:
    QLabel *label;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
};

class NodeTypePage : public QWizardPage
{
    Q_OBJECT

public:
    NodeTypePage(QWidget *parent = 0);

private:
    QLabel *label;
    QLabel *nameLabel;
    btNodeEditWidget *nodeEditor;

};



#endif // BTNEWTREEWIZARD_H
