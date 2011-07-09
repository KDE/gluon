#include "perceptionatomprivate.h"

using namespace BehaviorTree;

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
