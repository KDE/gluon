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

#include "nullpropertywidgetitem.h"

#include <QLabel>
#include <KLocalizedString>

// This is commented out specifically to inform you that this should not be done.
// As this class is not supposed to be used normally, it is a special case
// and as such does not register in the normal way (the registration would be a NOOP
// at any rate, as this does not support any data types. See the
// ::supportedDataTypes() function below)
// REGISTER_PROPERTYWIDGETITEM(GluonCreator,NullPropertyWidgetItem)

using namespace GluonCreator;

NullPropertyWidgetItem::NullPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    setEditWidget(new QLabel(i18n("Unknown Type")));
}

NullPropertyWidgetItem::~NullPropertyWidgetItem()
{

}

QList< QString >
NullPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    return supportedTypes;
}

PropertyWidgetItem*
NullPropertyWidgetItem::instantiate()
{
    return new NullPropertyWidgetItem();
}

void
NullPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("text", QString("Unknown: %1(%2)").arg(value.typeName()).arg(value.toString()));
}

#include "nullpropertywidgetitem.moc"