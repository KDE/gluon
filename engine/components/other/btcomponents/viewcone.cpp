#include "viewcone.h"

#include "viewconeprivate.h"
#include <engine/gameobject.h>
#include "character.h"
#include <smarts/lib/btperceptionviewcone.h>
#include <core/metainfo.h>

REGISTER_OBJECTTYPE(GluonEngine,ViewCone)

using namespace GluonEngine;

ViewCone::ViewCone(QObject * parent)
	: Component(parent)
{
	d = new ViewConePrivate();
    d->viewcone = new btPerceptionViewcone();
    metaInfo()->setPropertyRange("offsetAngleHorizontal", 0, 180);
    metaInfo()->setPropertyRange("offsetAngleVertical", 0, 180);
    metaInfo()->setPropertyRange("extentAngleHorizontal", 0, 180);
    metaInfo()->setPropertyRange("extentAngleVertical", 0, 180);
    metaInfo()->setPropertyRange("knowledgePrecision", 0, 1);
}

ViewCone::ViewCone(const ViewCone &other, QObject* parent)
	: Component(parent)
	, d(other.d)
{
	
}

ViewCone::~ViewCone()
{
}

QString ViewCone::category() const
{
    return QString(tr("Behavior Tree"));
}



void ViewCone::initialize()
{
        GluonEngine::Character * charComponent = 0;
        charComponent = qobject_cast<GluonEngine::Character*>(this->gameObject()->findComponentByType("GluonEngine::Character"));
	if(charComponent)
	{
		charComponent->addViewCone((btPerceptionViewcone*)this);
	}
	else
	{
		this->gameObject()->removeComponent(this);
	}
}

qreal ViewCone::offsetAngleHorizontal() const
{
	return d->viewcone->offsetAngleHorizontal;
}
void ViewCone::setOffsetAngleHorizontal(qreal value)
{
	d->viewcone->offsetAngleHorizontal = value;
}
			
qreal ViewCone::offsetAngleVertical() const
{
	return d->viewcone->offsetAngleVertical;
}

void ViewCone::setOffsetAngleVertical(qreal value)
{
	d->viewcone->offsetAngleVertical = value;
}

qreal ViewCone::extentAngleHorizontal() const
{
	return d->viewcone->extentAngleHorizontal;
}

void ViewCone::setExtentAngleHorizontal(qreal value)
{
	d->viewcone->extentAngleHorizontal = value;
}

qreal ViewCone::extentAngleVertical() const
{
	return d->viewcone->extentAngleVertical;
}

void ViewCone::setExtentAngleVertical(qreal value)
{
	d->viewcone->extentAngleVertical = value;
}

qreal ViewCone::radius() const
{
	return d->viewcone->radius;
}

void ViewCone::setRadius(qreal value)
{
	d->viewcone->radius = value;;
}

qreal ViewCone::knowledgePrecision() const
{
	return d->viewcone->knowledgePrecision;
}

void ViewCone::setKnowledgePrecision(qreal value)
{
	d->viewcone->knowledgePrecision = value;
}



#include "viewcone.moc"
