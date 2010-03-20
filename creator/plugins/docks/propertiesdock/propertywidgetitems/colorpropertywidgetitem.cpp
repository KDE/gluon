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

#include "colorpropertywidgetitem.h"

#include <QtGui/QColor>
#include <KColorButton>

#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, ColorPropertyWidgetItem)

using namespace GluonCreator;

class ColorPropertyWidgetItem::ColorPropertyWidgetItemPrivate
{
    public:
        ColorPropertyWidgetItemPrivate() { }

        KColorButton * button;
};

ColorPropertyWidgetItem::ColorPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    d = new ColorPropertyWidgetItemPrivate;

    d->button = new KColorButton(this);
    connect(d->button, SIGNAL(changed(const QColor&)), this, SLOT(colorValuechanged(const QColor&)));
    setEditWidget(d->button);
}

ColorPropertyWidgetItem::~ColorPropertyWidgetItem()
{
    delete d;
}

QList< QString >
ColorPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QColor");
    return supportedTypes;
}

PropertyWidgetItem*
ColorPropertyWidgetItem::instantiate()
{
    return new ColorPropertyWidgetItem();
}

void
ColorPropertyWidgetItem::setEditValue(const QVariant& value)
{
    QColor color = value.value<QColor>();
    d->button->setColor(color);
}

void
ColorPropertyWidgetItem::colorValuechanged(const QColor& value)
{
    PropertyWidgetItem::valueChanged(QVariant::fromValue<QColor>(value));
}

#include "colorpropertywidgetitem.moc"
