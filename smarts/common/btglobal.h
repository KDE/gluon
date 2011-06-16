#ifndef BTGLOBAL_H
#define BTGLOBAL_H

#include <QVariant>
#include "../lib/btlib_export.h"

struct BT_LIB_EXPORT btChildWeights 
{
    QVariantList childWeightList;
};

struct BT_LIB_EXPORT btParallelConditions
{
    QVariantList parallelConditions;
};

Q_DECLARE_METATYPE(btChildWeights)
Q_DECLARE_METATYPE(btParallelConditions)
#endif
