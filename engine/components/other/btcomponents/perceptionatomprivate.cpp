#include "perceptionatomprivate.h"

using namespace GluonEngine;

PerceptionAtomPrivate::PerceptionAtomPrivate()
{
}

PerceptionAtomPrivate::PerceptionAtomPrivate(const PerceptionAtomPrivate& other)
	: QSharedData(other)
	, atom(other.atom)
	, info(other.info)
{

}

PerceptionAtomPrivate::~PerceptionAtomPrivate()
{

}
