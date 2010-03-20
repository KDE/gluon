#ifndef KEYBOARDPRIVATE_H
#define KEYBOARDPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
    class KeyBoardPrivate : public QSharedData
    {
        public:
            KeyBoardPrivate();
            KeyBoardPrivate(KeyBoardPrivate &other);
    };
}

#endif