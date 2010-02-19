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

GluonObjectPropertyWidgetItem::GluonObjectPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
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
}

PropertyWidgetItem*
GluonObjectPropertyWidgetItem::instantiate()
{
    return new GluonObjectPropertyWidgetItem();
}

QList< QString >
GluonObjectPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    return supportedTypes;
}

void
GluonObjectPropertyWidgetItem::browseForItems()
{
    QList<const GluonCore::GluonObject*> projectItems = GluonObjectPWIPrivate::getChildrenOfType(typeName(), GluonEngine::Game::instance()->gameProject());
    QList<const GluonCore::GluonObject*> sceneItems =   GluonObjectPWIPrivate::getChildrenOfType(typeName(), GluonEngine::Game::instance()->currentScene()->sceneContents());
    
    if(projectItems.count() == 0 && sceneItems.count() == 0)
    {
        KMessageBox::information(this, i18n("There are no items of the type %1 anywhere in this project. Please add some and try again.").arg(typeName()), i18n("No Items Found"));
    }
    else
    {
        KMessageBox::information(this, i18n("Yay found some stuff! :D").arg(typeName()), i18n("%1 Items Found").arg(projectItems.count() + sceneItems.count()));
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
    PropertyWidgetItem::valueChanged(QVariant::fromValue<GluonCore::GluonObject*>(value));
}

#include "gluonobjectpropertywidgetitem.moc"
