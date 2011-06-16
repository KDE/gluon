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

#ifndef BTPROPERTYWIDGET_H
#define BTPROPERTYWIDGET_H

#include <QtGui/QWidget>
class btEditorNode;
class btEditorNodeType;
class QGridLayout;
class btDecoratorNode;
class ColorGen;
class QMenu;

class btPropertyWidget : public QWidget
{
Q_OBJECT;

public:
    btPropertyWidget(QObject * parent = 0);
    ~btPropertyWidget();
    
    btEditorNode * node() const;
    void setNode(btEditorNode * theNode);
    
public Q_SLOTS:
    void dragDropUpdate();
    void updateTreeModel();
    
Q_SIGNALS:
    void treeModelUpdate();
    
    
private:
    btEditorNode * m_node;
    ColorGen * colorgen;
    
    QWidget * createComponentPropertyView();
    
    void setupPropertyView();
    void appendToPropertyView (QGridLayout *layout, qint32 & row, QObject * name, QString description, QString value, bool enabled, QVariant options = 0);
    void appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btEditorNode * node, bool enabled);
    void appendComponentToPropertyView (QGridLayout *layout, qint32 &row, btEditorNodeType * node, bool enabled);
    void appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, bool enabled);
    QString getPropertyDescription(QObject *object, QString propertyName);
};

#endif // BTPROPERTYWIDGET_H
