#include "btnewtreewizard.h"

#include <QtGui>
#include <QDebug>
#include "bteditor.h"
#include "btnodeeditwidget.h"

NewTreeWizard::NewTreeWizard(QWidget *parent)
    : QWizard(parent)
 {
    addPage(new IntroPage);
    addPage(new NamePage);
    //addPage(new NodeTypePage);

    setWindowTitle(tr("New Behavior Tree Wizard"));
    bteditor* editor = static_cast<bteditor*>(parent);
    connect(
        this, SIGNAL(behaviorTreeCreated(QString)),
        editor, SLOT(newBehaviorTreeCreated(QString))
    );
}


void NewTreeWizard::accept()
{
    QString name = field("name").toString();
    emit behaviorTreeCreated(name);
    this->close();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    label = new QLabel(tr("This wizard will generate a new behavior tree "
                          "(more here later)"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

NamePage::NamePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Choose Name for Behavior Tree"));

    label = new QLabel(tr("This wizard will generate a new behavior tree "
                          "(more here later)"));
    label->setWordWrap(true);
    nameEdit = new QLineEdit;
    nameLabel = new QLabel(tr("Tree Name"));

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);

    registerField("name*", nameEdit);
    layout->addWidget(label);
    layout->addLayout(nameLayout);
    setLayout(layout);
}

NodeTypePage::NodeTypePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Add Node Types"));

    label = new QLabel(tr("Add new or existing node types to the project"
                          "(more here later)"));
    label->setWordWrap(true);
    nodeEditor = new btNodeEditWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(nodeEditor);
    setLayout(layout);
}

#include "btnewtreewizard.moc"
