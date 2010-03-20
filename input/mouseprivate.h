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

            QPoint m_position;
            QPoint m_originalPosition;
            double m_sensibility;
    };
}

#endif