#ifndef INPUTDETECTIONPRIVATE_H
#define INPUTDETECTIONPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
	class Detect;
	class InputDetectionPrivate : public QSharedData
	{
	public:
		InputDetectionPrivate();
		InputDetectionPrivate(InputDetectionPrivate &other);
		
		Detect * m_instance;
	};	
}
#endif