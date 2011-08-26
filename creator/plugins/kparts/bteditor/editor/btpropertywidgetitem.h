/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BTPROPERTYWIDGETITEM_H
#define BTPROPERTYWIDGETITEM_H

#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>

/**
 * The Property Widget Item is a class which will take an object and the name
 * of a property, and provide functionality for editing this property's value,
 * at the same time updating it in the object containing the project
 */
class btPropertyWidgetItem : public QWidget
{
Q_OBJECT;

public:
    btPropertyWidgetItem(QObject * parent = 0, Qt::WindowFlags f = 0);
    ~btPropertyWidgetItem();
    
    void setEditObject(QObject * editThis);
    void setEditProperty(QString propertyName, bool readOnly);
    
Q_SIGNALS:
    void sendUpdateTreeModel();
    
    
private Q_SLOTS:
    void propertyChanged(QVariant value);
    void propertyChanged(int value);
    void propertyChanged(double value);
    void propertyChanged(QString value);
    
    void QVariantListItemRemoved(QListWidgetItem * item, int index);
    void QVariantListItemAdded(QListWidgetItem * item);
    void QVariantListItemChanged(QListWidgetItem * item, int index);
    
private:
    void setupPropertyWidget(bool readOnly);

    QObject * editedObject;
    QString propertyName;
    
    QWidget *createLineEdit (QVariant value, bool enabled);
    QWidget *createSpinBox (QVariant value, bool enabled);
    QWidget *createDoubleSpinBox (QVariant value, bool enabled);
    QWidget *createList(QVariant value, bool enabled);
    QWidget *createChildProbabilitiesList(QString propertyName ,bool enabled);
	QWidget *createParallelConditionsList(QString propertyName, bool enabled);
    
    QWidget * editWidget;
    
    const QString getPropertyType(QString propertyName);
};

#endif // BTPROPERTYWIDGETITEM_H
