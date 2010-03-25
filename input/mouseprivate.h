#ifndef MOUSEPRIVATE_H
#define MOUSEPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QPoint>

namespace GluonInput
{
    class MousePrivate : public QSharedData
    {
        public:
            MousePrivate();
            MousePrivate(MousePrivate &other);

            QPoint position;
            QPoint originalPosition;
            double sensibility;
	    int hWheelPos;
	    int wheelPos;
    };
}

#endif