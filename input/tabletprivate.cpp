#include "tabletprivate.h"

using namespace GluonInput;

TabletPrivate::TabletPrivate()
{
}

TabletPrivate::TabletPrivate(TabletPrivate &other)
	: QSharedData(other)
{
}