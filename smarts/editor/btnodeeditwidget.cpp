#include "btnodeeditwidget.h"
#include "btnodemodel.h"
#include "btnodetypesmodelnode.h"
#include <QDebug>
#include <QtGui/QValidator>
#include <QtGui/QItemEditorFactory>
#include "bttreemodel.h"

#include <QtGui/QLineEdit>
#include "btqlistdelegate.h"

#include <QtGui/QSpinBox>

btNodeEditWidget::btNodeEditWidget(QWidget * parent)
{
    model = 0;
    m_selectedNode = 0;
    mainLayout      = new QVBoxLayout(this);
    buttonLayout    = new QHBoxLayout();
    editLayout      = new QGridLayout();

    name            = new QLabel(tr("Name"));
    classname       = new QLabel(tr("Classname"));
    discription     = new QLabel(tr("Discription"));
    properties      = new QLabel(tr("Properties"));

    QRegExp re("[A-Za-z]{1,1}[A-Za-z0-9_]{0,}");
    QRegExpValidator* v = new QRegExpValidator(re, this);
    nameedit        = new QLineEdit();
    classnameedit   = new QLineEdit();
    classnameedit->setValidator(v);
    discriptionedit = new QLineEdit();

    add_button      = new QPushButton(tr("Add Property"));
    remove_button   = new QPushButton(tr("Remove Property"));

    propertyList    = new QTableView();

    editLayout->addWidget(name,0,0);
    editLayout->addWidget(nameedit,0,1);
    editLayout->addWidget(classname,0,2);
    editLayout->addWidget(classnameedit,0,3);
    editLayout->addWidget(discription,1,0);
    editLayout->addWidget(discriptionedit,1,1,1,3);

    buttonLayout->addStretch();
    buttonLayout->addWidget(add_button);
    buttonLayout->addWidget(remove_button);

    mainLayout->addLayout(editLayout);
    mainLayout->addWidget(properties);  
    mainLayout->addWidget(propertyList);
    mainLayout->addLayout(buttonLayout);

    connectSignals();

    connect(classnameedit, SIGNAL(textChanged(QString)), this, SLOT(classnameEdited(QString)));
    connect(discriptionedit, SIGNAL(textChanged(QString)), this, SLOT(descriptionEdited(QString)));
    connect(add_button,SIGNAL(clicked()),this,SLOT(add_button_clicked()));
    connect(remove_button,SIGNAL(clicked()),this,SLOT(remove_button_clicked()));
    
    delegate = new btQListDeletgate(this);
    propertyList->setItemDelegateForColumn(1, delegate);
}

void btNodeEditWidget::connectSignals()
{
    connect(nameedit, SIGNAL(textChanged(QString)), this, SLOT(nameEdited(QString)));
}

void btNodeEditWidget::disconnectSignals(btTreeModel * currentBehaviorTree)
{
    if(currentBehaviorTree && model)
        connect(model, SIGNAL(updatePropertyWidget()), currentBehaviorTree, SIGNAL(addRemoveBTNode()));
    
    disconnect(nameedit, SIGNAL(textChanged(QString)), this, SLOT(nameEdited(QString)));
}

btNodeEditWidget::~btNodeEditWidget()
{
    delete model; // qDelete
    delete delegate;
}

void btNodeEditWidget::setModel(btnodemodel* btmodel)
{
    delete model;
    model = btmodel;

    propertyList->setModel(model);

    nameedit->setText(model->name());
    classnameedit->setText(model->classname());
    discriptionedit->setText(model->description());
}

void btNodeEditWidget::setSelectedNode(btNodeTypesModelNode* selectedNode)
{
    m_selectedNode = selectedNode;
}

void btNodeEditWidget::nameEdited(QString name){
    model->setName(name);
    if(m_selectedNode){
        m_selectedNode->setName(name);
    }
}

void btNodeEditWidget::classnameEdited(QString classname){
    model->setClassname(classname);
}

void btNodeEditWidget::descriptionEdited(QString description){
    model->setDescription(description);
}

void btNodeEditWidget::add_button_clicked()
{
    model->insertRows(model->rowCount(),1);
}

void btNodeEditWidget::remove_button_clicked()
{
    if(propertyList->currentIndex().isValid()){
        model->removeRows(propertyList->currentIndex().row(),1);
    }
}

#include "btnodeeditwidget.moc"
