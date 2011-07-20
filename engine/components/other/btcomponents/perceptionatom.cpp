#include "perceptionatom.h"

#include "perceptionatomprivate.h"
#include "character.h"
#include <smarts/lib/btperceptionatom.h>
#include <engine/gameobject.h>

REGISTER_OBJECTTYPE(GluonEngine, PerceptionAtom)

using namespace GluonEngine;

PerceptionAtom::PerceptionAtom(QObject* parent): Component(parent)
{
	d = new PerceptionAtomPrivate();
	d->atom = new btPerceptionAtom();
	d->info = 0;
}

PerceptionAtom::PerceptionAtom(const PerceptionAtom& other, QObject* parent)
	: Component(parent)
	, d(other.d)
{

}

void PerceptionAtom::initialize()
{
    GluonEngine::Character * charComponent = 0;
        charComponent = qobject_cast<GluonEngine::Character*>(this->gameObject()->findComponentByType("GluonEngine::Character"));
	if(charComponent)
	{
		charComponent->addPerceptionAtom((btPerceptionAtom*)this);
	}
	else
	{
		this->gameObject()->removeComponent(this);
	}
}

PerceptionAtom::~PerceptionAtom()
{

}

QString PerceptionAtom::category() const
{
    return QString(tr("Behavior Tree"));
}

QVariant PerceptionAtom::knowledge() const
{
	return d->atom->knowledge();
}

GluonEngine::PerceptionInfo* PerceptionAtom::perceptionInfo() const
{
	return d->info;
}

void PerceptionAtom::setPerceptionInfo(GluonEngine::PerceptionInfo* info)
{
	d->info = info;
	d->atom->setPerceptionInfo(info->getBtPerceptionInfo());
}

qreal PerceptionAtom::precision() const
{
	d->atom->precision();
}

void PerceptionAtom::setPrecision(qreal precision)
{
	d->atom->setPrecision(precision);
}

void PerceptionAtom::setShouldUpdate(bool update)
{
	d->atom->setShouldUpdate(update);
}

bool PerceptionAtom::shouldUpdate() const
{
	return d->atom->shouldUpdate();
}



#include "perceptionatom.moc"
