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

#include "qfontpropertywidgetitem.h"

#include <KFontRequester>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, QFontPropertyWidgetItem);

using namespace GluonCreator;

QFontPropertyWidgetItem::QFontPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
        : PropertyWidgetItem(parent, f)
{
    KFontRequester * theFontReq = new KFontRequester(this);
    connect(theFontReq, SIGNAL(fontSelected(const QFont&)), this, SLOT(fontChanged(const QFont&)));
    setEditWidget(theFontReq);
}

QFontPropertyWidgetItem::~QFontPropertyWidgetItem()
{
}

QList< QString >
QFontPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QFont");
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem*
QFontPropertyWidgetItem::instantiate()
{
    return new QFontPropertyWidgetItem();
}

void
QFontPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("font", value);
    GluonCreator::PropertyWidgetItem::setEditValue(value);
}

void QFontPropertyWidgetItem::fontChanged(const QFont& value)
{
    PropertyWidgetItem::valueChanged(QVariant(value));
}


#include "qfontpropertywidgetitem.moc"
