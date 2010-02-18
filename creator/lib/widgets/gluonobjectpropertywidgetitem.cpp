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
#include "core/gluonobject.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

Q_DECLARE_METATYPE(GluonCore::GluonObject*);

using namespace GluonCreator;

GluonObjectPropertyWidgetItem::GluonObjectPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
    QHBoxLayout * base = new QHBoxLayout;
    base->setSpacing(0);
    base->setContentsMargins(0, 0, 0, 0);

    currentValue = new QLabel(this);
    base->addWidget(currentValue);
    
    browseButton = new QPushButton(this);
    browseButton->setText("...");
    base->addWidget(browseButton);
    
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
