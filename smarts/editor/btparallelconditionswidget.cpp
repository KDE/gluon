#include "btparallelconditionswidget.h"

#include "btglobal.h"
#include "bteditornodetype.h"
#include "btnode.h"

#include <QtCore/QVariant>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QRadioButton>
#include <QtGui/QGroupBox>

btParallelConditionsWidget::btParallelConditionsWidget(QWidget * parent) : QWidget(parent)
{
	parallelConditionsLayout = new QVBoxLayout(this);
}

btParallelConditionsWidget::~btParallelConditionsWidget()
{
	qDeleteAll(parallelConditionsLayout->children());
	delete parallelConditionsLayout;
}

void btParallelConditionsWidget::setParallelConditions(QString propertyName, QObject* object, bool enabled)
{
	qRegisterMetaType<btParallelConditions>("btParallelConditions");
    
    btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(object);
    btNode* node = qobject_cast<btNode*>(nodeType->parentNode());
    
    if(!nodeType->property(propertyName.toUtf8()).isValid())
    {
        btParallelConditions pc;
        QVariant v;
        v.setValue(pc);
        nodeType->setProperty(propertyName.toUtf8(), v);
    }
	
	btParallelConditions conditionsList = nodeType->property(propertyName.toUtf8()).value<btParallelConditions>();
    for (int i = 0; i < node->childCount(); i++) 
    {
        
        QGroupBox * group = new QGroupBox(node->child(i)->name());
        group->setFlat(true);
        
		QRadioButton * sRButton = new QRadioButton(this);
		sRButton->setEnabled(enabled);
		sRButton->setText("Succeeded");
		QRadioButton * fRButton = new QRadioButton(this);
		fRButton->setEnabled(enabled);
		fRButton->setText("Failed");
        QRadioButton * rRButton = new QRadioButton(this);
        rRButton->setEnabled(enabled);
        rRButton->setText("Running");
        
        QVBoxLayout * vbox = new QVBoxLayout();
        
       //parallelConditionsLayout->addWidget(nodeName);
        vbox->addWidget(sRButton);
		vbox->addWidget(fRButton);
        vbox->addWidget(rRButton);
        
        group->setLayout(vbox);
        parallelConditionsLayout->addWidget(group);
        
        if(i > conditionsList.parallelConditions.count()-1)
        {
            conditionsList.parallelConditions.append(1.0);
            sRButton->setChecked(true);
        }
        else
        {
            double value = conditionsList.parallelConditions[i].toDouble();
            
            if(value >= 1.0)
            {
                sRButton->setChecked(true);
            }
            else if (value == 0.0)
            {
                fRButton->setChecked(true);
            }
            else if(value < 0.0)
            {
                rRButton->setChecked(true);
            }
        }
        
        connect(sRButton, SIGNAL(toggled(bool)), node->child(i)->type(), SLOT(changeCondition(bool)));
        connect(fRButton, SIGNAL(toggled(bool)), node->child(i)->type(), SLOT(changeCondition(bool)));
        connect(rRButton, SIGNAL(toggled(bool)), node->child(i)->type(), SLOT(changeCondition(bool)));
		
    }
    QVariant v;
    v.setValue(conditionsList);
    nodeType->setProperty(propertyName.toUtf8(), v);
    this->setLayout(parallelConditionsLayout);
}

#include "btparallelconditionswidget.moc"
