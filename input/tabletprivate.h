#ifndef TABLETPRIVATE_H
#define TABLETPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
    class TabletPrivate : public QSharedData
    {
        public:
            TabletPrivate();
            TabletPrivate(TabletPrivate &other);
    };
}

#endif