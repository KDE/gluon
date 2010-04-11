#include "qrealpropertywidgetitem.h"

#include <QtGui/QDoubleSpinBox>

#include <cfloat>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, QRealPropertyWidgetItem)

using namespace GluonCreator;

QRealPropertyWidgetItem::QRealPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
        : PropertyWidgetItem(parent, f)
{
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
    setEditWidget(spinBox);
    connect(editWidget(), SIGNAL(valueChanged(double)), SLOT(qrealValueChanged(double)));
}

QRealPropertyWidgetItem::~QRealPropertyWidgetItem()
{
}

QList< QString >
QRealPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("qreal");
    return supportedTypes;
}

PropertyWidgetItem*
QRealPropertyWidgetItem::instantiate()
{
    return new QRealPropertyWidgetItem();
}

void
QRealPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("value", value);
}

void
QRealPropertyWidgetItem::qrealValueChanged(double value)
{
    PropertyWidgetItem::valueChanged(QVariant(value));
}

#include "qrealpropertywidgetitem.moc"
