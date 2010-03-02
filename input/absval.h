#ifndef ABSVAL_H
#define ABSVAL_H

#include "gluon_input_export.h"

namespace GluonInput
{
	class GLUON_INPUT_EXPORT AbsVal
	{
	public:
		AbsVal(int v = 0, int m = 0, int M = 0, int f = 0, int F = 0) {
			value = v;
			min = m;
			max = M;
			flat = f;
			fuzz = F;
		}
		int value;
		int min;
		int max;
		int flat;
		int fuzz;
	};
}

#endif