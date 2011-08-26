#include <QtGui>

#include "btglobal.h"
#include "btqlistdelegate.h"
//#include <QMetaType>

btQListDeletgate::btQListDeletgate(QObject *parent)
: QItemDelegate(parent)
{
}

QWidget *btQListDeletgate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
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
