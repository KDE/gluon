/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "gluonobjectpropertywidgetitem.h"
#include "engine/game.h"
#include "engine/scene.h"
#include "engine/gameobject.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <core/gameproject.h>
#include <KMessageBox>
#include <KLocalizedString>
#include <KInputDialog>

Q_DECLARE_METATYPE(GluonCore::GluonObject*);

namespace GluonCreator
{
    class GluonObjectPWIPrivate
    {
        public:
            GluonObjectPWIPrivate()
            {
                currentValue = 0;
                browseButton = 0;
            };
            
            QLabel * currentValue;
            QPushButton * browseButton;
            QString typeName;
            
            static QList<const GluonCore::GluonObject*> getChildrenOfType(const QString &typeName, const GluonCore::GluonObject* lookHere)
            {
                QList<const GluonCore::GluonObject*> foundChildren;
                
                foreach(const QObject *child, lookHere->children())
                {
                    if(child->inherits(typeName.toUtf8()))
                        foundChildren.append(qobject_cast<const GluonCore::GluonObject*>(child));
                        
                    foundChildren.append(getChildrenOfType(typeName, qobject_cast<const GluonCore::GluonObject*>(child)));
                }
                
                return foundChildren;
            }
    };
}

using namespace GluonCreator;

GluonObjectPropertyWidgetItem::GluonObjectPropertyWidgetItem(const QString &typeName, QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
    d = new GluonObjectPWIPrivate;
    d->typeName = typeName;
    
    QHBoxLayout * base = new QHBoxLayout;
    base->setSpacing(0);
    base->setContentsMargins(0, 0, 0, 0);

    d->currentValue = new QLabel(this);
    d->currentValue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    base->addWidget(d->currentValue);
    
    d->browseButton = new QPushButton(this);
    d->browseButton->setText("...");
    connect(d->browseButton, SIGNAL(clicked(bool)), this, SLOT(browseForItems()));
    base->addWidget(d->browseButton);
    
    QWidget * local = new QWidget(parent);
    local->setLayout(base);
    layout()->addWidget(local);
}

GluonObjectPropertyWidgetItem::~GluonObjectPropertyWidgetItem()
{
    delete(d);
}

PropertyWidgetItem*
GluonObjectPropertyWidgetItem::instantiate()
{
    return new GluonObjectPropertyWidgetItem(QString());
}

QList< QString >
GluonObjectPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    return supportedTypes;
}

void
GluonObjectPropertyWidgetItem::setTypeName(const QString& typeName)
{
    d->typeName = typeName;
}

QString
GluonObjectPropertyWidgetItem::typeName() const
{
    return d->typeName;
}

void
GluonObjectPropertyWidgetItem::browseForItems()
{
    QList<const GluonCore::GluonObject*> items = GluonObjectPWIPrivate::getChildrenOfType(d->typeName, GluonEngine::Game::instance()->gameProject());
    items.append(GluonObjectPWIPrivate::getChildrenOfType(d->typeName, GluonEngine::Game::instance()->currentScene()->sceneContents()));
    
    if(items.count() == 0)
    {
        KMessageBox::information(this, i18n("There are no items of the type %1 anywhere in this project. Please add some and try again.").arg(d->typeName), i18n("No Items Found"));
    }
    else
    {
        QString caption("");
        QString label("");
        QStringList nameList;
        bool ok = false;
        
        nameList.append(i18n("Clear object reference"));
        foreach(const GluonCore::GluonObject *item, items)
            nameList.append(item->fullyQualifiedName());
        
        QString chosen = KInputDialog::getItem(caption, label, nameList, 0, false, &ok, this);
        if(ok)
        {
            GluonCore::GluonObject *chosenItem = NULL;
            foreach(const GluonCore::GluonObject *testItem, items)
            {
                if(testItem->fullyQualifiedName() == chosen)
                {
                    chosenItem = const_cast<GluonCore::GluonObject*>(testItem);
                    break;
                }
            }
            objectValueChanged(chosenItem);
        }
    }
}

void
GluonObjectPropertyWidgetItem::setEditValue(const QVariant& value)
{
    PropertyWidgetItem::setEditValue(value);
}

void
GluonObjectPropertyWidgetItem::objectValueChanged(GluonCore::GluonObject * value)
{
    if(value)
        d->currentValue->setText(value->name());
    else
        d->currentValue->setText("");
    QVariant newValue = QVariant::fromValue<GluonCore::GluonObject*>(value);
    PropertyWidgetItem::valueChanged(newValue);
}

#include "gluonobjectpropertywidgetitem.moc"
