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

#include "enumpropertywidgetitem.h"
#include "core/debughelper.h"

#include <QtGui/QComboBox>
#include <QtGui/QLayout>
#include <QtCore/QMetaEnum>

namespace GluonCreator
{
    class EnumPWIPrivate
    {
        public:
            EnumPWIPrivate() { comboBox = 0; editObject = 0; };
            ~EnumPWIPrivate() {};
            
            QComboBox * comboBox;
            QObject * editObject;
            QString typeName;
            QMetaEnum metaEnum;
            
            void setupComboBox()
            {
                DEBUG_BLOCK
                if(!editObject)
                    return;
                
                const QMetaObject * mo = editObject->metaObject();
                int enumIndex = mo->indexOfEnumerator(typeName.toUtf8());
                if(enumIndex > -1)
                    metaEnum = mo->enumerator(enumIndex);
                else
                    metaEnum = QMetaEnum();
                
                DEBUG_TEXT(QString("Adding %1 items from the enum %2 (requested: %3)").arg(metaEnum.keyCount()).arg(metaEnum.name()).arg(typeName));
                for(int i = 0; i < metaEnum.keyCount(); ++i)
                {
                    comboBox->addItem(QString(metaEnum.key(i)), QVariant(i));
                }
            }
    };
}

using namespace GluonCreator;

EnumPropertyWidgetItem::EnumPropertyWidgetItem(const QString& typeName, QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
    d = new EnumPWIPrivate();
    d->typeName = typeName;
    
    d->comboBox = new QComboBox(this);
    layout()->addWidget(d->comboBox);
}

EnumPropertyWidgetItem::~EnumPropertyWidgetItem()
{
    delete d;
}

PropertyWidgetItem*
EnumPropertyWidgetItem::instantiate()
{
    return new EnumPropertyWidgetItem(QString());
}

QList< QString >
EnumPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    return supportedTypes;
}

void
EnumPropertyWidgetItem::setEditObject(QObject* editThis)
{
    GluonCreator::PropertyWidgetItem::setEditObject(editThis);
    d->editObject = editThis;
    d->setupComboBox();
}

void
EnumPropertyWidgetItem::setEditValue(const QVariant& value)
{
    GluonCreator::PropertyWidgetItem::setEditValue(value);
}

void
EnumPropertyWidgetItem::indexChanged(int newIndex)
{
    //GluonCreator::PropertyWidgetItem::valueChanged( QVariant::fromValue<>() );
}

#include "enumpropertywidgetitem.moc"
