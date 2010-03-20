#ifndef CODE_H
#define CODE_H

#define GLUONINPUT_CODE_BUTTON_SIZE 232
#define GLUONINPUT_CODE_RELABS_SIZE 198

#include "gluon_input_export.h"
#include "keydefinitions.h"

#include <QtCore/QString>
#include <QtCore/QEvent>

namespace GluonInput
{
	class GLUON_INPUT_EXPORT Code
	{
	public:
		static QString buttonName(int code);
		static QString eventName(int code);
		static QString relAxisName(int code);
		static QString absAxisName(int code);

	private:

	};
}
#endif // KCLCODE_H
