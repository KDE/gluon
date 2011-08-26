#include "btnodemodel.h"
#include "btnodetypesmodel.h"
#include "bteditornodetype.h"
#include <QDebug>
#include <QIcon>

btnodemodel::btnodemodel(btEditorNodeType * nodetype,QObject *parent)
: QAbstractTableModel(parent)
{
    node = nodetype;
}

int btnodemodel::rowCount(const QModelIndex &parent) const
{
    return node->dynamicPropertyNames().count();
}

int btnodemodel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant btnodemodel::data(const QModelIndex &index, int role) const
{    
    if (!index.isValid())
        return QVariant();
    
    if (index.row() >= node->dynamicPropertyNames().count())
        return QVariant();
    
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
            case 0:
               return node->dynamicPropertyNames().at(index.row());
            case 1:
                return node->property(node->dynamicPropertyNames().at(index.row()));
            case 2:
                return node->getPropertyDescription(node->dynamicPropertyNames().at(index.row()));
            default:
                return QVariant();
        }
    }
    else if(role == Qt::EditRole)
    {
        switch(index.column())
        {
            case 0:
                return node->dynamicPropertyNames().at(index.row());
            case 1:
                return node->property(node->dynamicPropertyNames().at(index.row()));
            case 2:
                return node->getPropertyDescription(node->dynamicPropertyNames().at(index.row()));
            default:
                return QVariant();
        }
        
    }
    else
    {
        return QVariant();
    }
}

QVariant btnodemodel::headerData(int section, Qt::Orientation orientation,
                                 int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    
    if (orientation == Qt::Horizontal){
        switch(section){
            case 0:
                return QString("Name");
            case 1:
                return QString("Datatype");
            case 2:
                return QString("Description");
            default:
                return QString("Column %1").arg(section);
        }
        
    }else{
        return QString("Prop %1").arg(section);
    }
}

Qt::ItemFlags btnodemodel::flags(const QModelIndex &index) const
{
    if(!index.isValid()){
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool btnodemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        QString newName = value.toString();
        QString oldName = node->dynamicPropertyNames().at(index.row());
        
        if(newName != "" && newName != oldName)
        {
            switch (index.column()) 
            {
                case 0:
                    node->setProperty(newName.toUtf8(),node->property(oldName.toUtf8()));
                    emit node->emitPropertyChangedSignal(newName, node->property(oldName.toUtf8()));
                    
                    node->setPropertyDescription(newName, oldName, node->getPropertyDescription(oldName));
                    emit node->emitPropertyDescriptionChangedSignal(newName, oldName, newName);
                    
                    node->setProperty(oldName.toUtf8(),QVariant::Invalid);
                    emit node->emitPropertyChangedSignal(oldName, QVariant::Invalid);
                    break;
                case 1:
                    node->setProperty(oldName.toUtf8(),newName);
                    emit node->emitPropertyChangedSignal(oldName, newName);
                    break;
                case 2:
                    node->setPropertyDescription(oldName, newName);
                    emit node->emitPropertyDescriptionChangedSignal(oldName, "", newName);
                    break;
            }
            emit updatePropertyWidget();
            emit dataChanged(index,index);
            return true;
        }
    }
    return false;
}

bool btnodemodel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(parent, position, position+rows-1);
    
    
    int propertyCount = node->dynamicPropertyNames().count();
    		
    for(int i = 0; i < propertyCount; i++){
        if(node->property((tr("newProperty") + QString::number(i + position)).toUtf8()) != QVariant::Invalid){
            continue;
        }else{
            position = position + i;
            break;
        }
    }
    
    node->setProperty((tr("newProperty") + QString::number(position)).toUtf8(), "QString");
    
    endInsertRows();
    
    emit node->emitPropertyChangedSignal((tr("newProperty") + QString::number(position)).toUtf8(), "QString");
    emit updatePropertyWidget();
    emit dataChanged(parent,parent);
    
    return true;
}

bool btnodemodel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(parent, position, position+rows-1);
    
    if(node->dynamicPropertyNames().count() > position){
        QString propertyName = node->dynamicPropertyNames().at(position);
        node->setProperty(propertyName.toUtf8(),QVariant::Invalid);
        node->removePropertyDescription(propertyName);
        emit node->emitPropertyDescriptionChangedSignal("", propertyName, "");
        emit node->emitPropertyChangedSignal(propertyName, QVariant::Invalid);
        emit updatePropertyWidget();
    }
    
    endRemoveRows();
    return true;
}

QString btnodemodel::name() const
{
    return node->name();
}

void btnodemodel::setName(QString name)
{
    node->setName(name);
    node->emitNameChanged(name);
}

QString btnodemodel::description() const
{
    return node->description();
}

void btnodemodel::setDescription(QString description)
{
    node->setDescription(description);
    node->emitDescriptionChanged(description);
}

QString btnodemodel::classname() const
{
    return node->className();
}

void btnodemodel::setClassname(QString classname)
{
    node->setClassName(classname);
    node->emitClassNameChanged(classname);
}

#include "btnodemodel.moc"
