#ifndef QREALPROPERTYWIDGETITEM_H
#define QREALPROPERTYWIDGETITEM_H

#include "widgets/propertywidgetitem.h"

class QDoubleSpinBox;

namespace GluonCreator
{
	class QRealPropertyWidgetItem : public PropertyWidgetItem
	{
		    Q_OBJECT
        public:
            explicit QRealPropertyWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~QRealPropertyWidgetItem();

            virtual QList<QString> supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public slots:
            void setEditValue(const QVariant& value);
            void qrealValueChanged(double value);

	};
}

#endif
