/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "propertywidgetitemnewcustomproperty.h"

#include <QtGui/QTextEdit>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QPushButton>

#include <klocalizedstring.h>
#include <core/gluonobject.h>

using namespace GluonCreator;

PropertyWidgetItemNewCustomProperty::PropertyWidgetItemNewCustomProperty(QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    propertyName = new QTextEdit(this);
    propertyName->setAcceptRichText(false);

    propertyType = new QComboBox(this);
    propertyType->addItem(ki18n("Boolean (bool)").toString(), QVariant::fromValue<bool>(false));
    propertyType->addItem(ki18n("Integer (int)").toString(), QVariant::fromValue<int>(0));
    propertyType->addItem(ki18n("Color (QColor)").toString(), QVariant::fromValue<QColor>(QColor()));
    propertyType->addItem(ki18n("Double precision floating point (double)").toString(), QVariant::fromValue<double>(0));
    propertyType->addItem(ki18n("Floating point (float)").toString(), QVariant::fromValue<float>(0));
//    propertyType->addItem(ki18n("").toString(), QString(""));
    
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(ki18n("Name:").toString(), propertyName);
    formLayout->addRow(ki18n("Type").toString(), propertyType);
    
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(formLayout);
    layout->addStretch();
    
    QFrame* frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Sunken | QFrame::HLine);
    layout->addWidget(frame);
    
    QPushButton* okButton = new QPushButton(ki18n("Add Property").toString(), this);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(createPropertyClicked()));
    layout->addWidget(okButton);
    
    setLayout(layout);
}

void PropertyWidgetItemNewCustomProperty::createProperty(GluonCore::GluonObject* editThis)
{
    editingThis = editThis;
    show();
}

void PropertyWidgetItemNewCustomProperty::createPropertyClicked()
{
    editingThis->setProperty( propertyName->toPlainText().toUtf8(), propertyType->itemData( propertyType->currentIndex() ) );
    hide();
    emit propertyCreated( editingThis, propertyName->toPlainText() );
}
