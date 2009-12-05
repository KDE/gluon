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

using namespace Gluon::Creator;


Gluon::Creator::NullPropertyWidgetItem::NullPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    setEditWidget(new QLabel(i18n("Unknown Type")));
}

Gluon::Creator::NullPropertyWidgetItem::~NullPropertyWidgetItem()
{

}

void Gluon::Creator::NullPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("text", QString("Unknown Type: %1").arg(value.toString()));
}

#include "nullpropertywidgetitem.moc"