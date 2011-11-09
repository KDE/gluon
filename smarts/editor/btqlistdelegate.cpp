/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "btqlistdelegate.h"

#include "btglobal.h"

#include <QtGui/QComboBox>
//#include <QMetaType>

btQListDeletgate::btQListDeletgate(QObject *parent)
: QItemDelegate(parent)
{
}

QWidget *btQListDeletgate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    //qRegisterMetaType<btChildWeights>("btChildWeights");
	//qRegisterMetaType<btParallelConditions>("btParallelConditions");
    
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItem("int", QVariant("int"));
    comboBox->addItem("QString", QVariant("QString"));
    comboBox->addItem("double", QVariant("double"));
    comboBox->addItem("QVariantList", QVariant("QVariantList"));
    //comboBox->addItem("btChildWeights", QVariant("btChildWeights"));
    comboBox->setCurrentIndex(comboBox->findData(index.data()));
    return comboBox;
}

void btQListDeletgate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(value));//comboBox->findData(value));
}

void btQListDeletgate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void btQListDeletgate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

#include "btqlistdelegate.moc"
