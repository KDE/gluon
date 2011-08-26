#include "btchildlistwidget.h"

#include "btglobal.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVariant>
#include <QtGui/QVBoxLayout>

#include "btnode.h"
#include "bteditornodetype.h"

btChildListWidget::btChildListWidget(QWidget * parent) : QWidget(parent)
{
    childLayout = new QVBoxLayout(this);
}

btChildListWidget::~btChildListWidget()
{
}

void btChildListWidget::setChildProbabilites(QString propertyName ,QObject* object, bool enabled)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(object);
    btNode* node = qobject_cast<btNode*>(nodeType->parentNode());
    
    if(!nodeType->property(propertyName.toUtf8()).isValid())
    {
        btChildWeights cw;
        QVariant v;
        v.setValue(cw);
        nodeType->setProperty(propertyName.toUtf8(), v);
    }
    
    btChildWeights probList = nodeType->property(propertyName.toUtf8()).value<btChildWeights>();
    for (int i = 0; i < node->childCount(); i++) 
    {        
        QLabel * nodeName = new QLabel(this);
        nodeName->setText(node->child(i)->name());
        
        QDoubleSpinBox * prob = new QDoubleSpinBox(this);
        prob->setRange(0.0, 1.0);
        prob->setSingleStep(0.01);
        prob->setEnabled(enabled);
        
        if(i > probList.childWeightList.count()-1)
        {
            probList.childWeightList.append(0.5);
            prob->setValue(0.5);
        }
        else
        {
            prob->setValue(probList.childWeightList[i].toDouble());
        }
        
        connect(prob, SIGNAL(valueChanged(double)), node->child(i)->type(), SLOT(changeProbability(double)));
        
        childLayout->addWidget(nodeName);
        childLayout->addWidget(prob);

    }
    QVariant v;
    v.setValue(probList);
    nodeType->setProperty(propertyName.toUtf8(), v);
    this->setLayout(childLayout);
}

#include "btchildlistwidget.moc"
