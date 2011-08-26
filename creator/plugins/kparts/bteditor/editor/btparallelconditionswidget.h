#ifndef BTPARALLELCONDITIONSWIDGET_H
#define BTPARALLELCONDITIONSWIDGET_H

#include <QWidget>
#include <QObject>

class QVBoxLayout;

class btParallelConditionsWidget : public QWidget 
{
	Q_OBJECT
public:
	btParallelConditionsWidget(QWidget * parent = 0);
	~btParallelConditionsWidget();
	
	void setParallelConditions(QString propertyName, QObject* object, bool enabled);
	
private:
	QVBoxLayout* parallelConditionsLayout;
};

#endif