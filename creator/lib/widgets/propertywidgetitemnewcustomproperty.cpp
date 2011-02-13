/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "propertywidgetitemnewcustomproperty.h"

#include "objectmanager.h"
#include "core/gluonobject.h"

#include <KDE/KLocalizedString>

#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QPushButton>
#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtGui/QQuaternion>

#include <QtCore/QUrl>
#include <QtCore/QSizeF>

using namespace GluonCreator;

PropertyWidgetItemNewCustomProperty::PropertyWidgetItemNewCustomProperty(QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    propertyName = new QLineEdit(this);

    propertyType = new QComboBox(this);
    propertyType->addItem(i18n("Boolean (bool)"), QVariant::fromValue<bool>(false));
    propertyType->addItem(i18n("Integer (int)"), QVariant::fromValue<int>(0));
    propertyType->addItem(i18n("Color (rgba)"), QVariant::fromValue<QColor>(QColor()));
    propertyType->addItem(i18n("Double precision floating point (double)"), QVariant::fromValue<double>(0));
    propertyType->addItem(i18n("Floating point (float)"), QVariant::fromValue<float>(0));
    propertyType->addItem(i18n("Large integer (longlong)"), QVariant::fromValue<qlonglong>(0));
    propertyType->addItem(i18n("String (string)"), QVariant::fromValue<QString>(""));
    propertyType->addItem(i18n("2D Vector (vector2d)"), QVariant::fromValue<QVector2D>(QVector2D()));
    propertyType->addItem(i18n("3D Vector (vector3d)"), QVariant::fromValue<QVector3D>(QVector3D()));
    propertyType->addItem(i18n("4D Vector (vector4d)"), QVariant::fromValue<QVector4D>(QVector4D()));
    propertyType->addItem(i18n("Quaternion (quaternion)"), QVariant::fromValue<QQuaternion>(QQuaternion()));
    propertyType->addItem(i18n("Unsigned integer (uint)"), QVariant::fromValue<uint>(0));
    propertyType->addItem(i18n("Unsigned large integer (ulonglong)"), QVariant::fromValue<qulonglong>(0));
    propertyType->addItem(i18n("URL (url)"), QVariant::fromValue<QUrl>(QUrl()));
    propertyType->addItem(i18n("2D size (size2d)"), QVariant::fromValue<QSizeF>(QSizeF()));
    QHash<QString, const QMetaObject* > objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    QHash<QString, const QMetaObject* >::const_iterator i;
    for(i = objectTypes.constBegin(); i != objectTypes.constEnd(); ++i)
    {
        QObject* obj = i.value()->newInstance();
        GluonCore::GluonObject* gObj = qobject_cast< GluonCore::GluonObject* >(obj);
        if(gObj)
        {
            QString humanName = ObjectManager::instance()->humanifyClassName(i.key());
            propertyType->addItem(humanName, gObj->toVariant(0));
        }
    }

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(i18n("Name:"), propertyName);
    formLayout->addRow(i18n("Type"), propertyType);

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
    editingThis->setProperty( propertyName->text().toUtf8(), propertyType->itemData( propertyType->currentIndex() ) );
    hide();
    emit propertyCreated( editingThis, propertyName->text() );
}
