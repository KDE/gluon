#include "btperceptioninfoscriptable.h"

#include <QtGui/QVector3D>
#include "perceptioninfo.h"

using namespace GluonEngine;

btPerceptionInfoScriptable::btPerceptionInfoScriptable(QObject* parent)
	: btPerceptionInfo(parent)
{
	setPosition(QVector3D());
	setRadius(0);
}

btPerceptionInfoScriptable::~btPerceptionInfoScriptable()
{

}

QVariant btPerceptionInfoScriptable::getAdjustedValue(qreal precision) const
{
	PerceptionInfo * parent = qobject_cast< PerceptionInfo* >(this->parent());
	return parent->getAdjustedValue(precision);
}

#include "btperceptioninfoscriptable.moc"
