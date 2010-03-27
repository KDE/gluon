#ifndef CUSTOMINPUTPRIVATE_H
#define CUSTOMINPUTPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QPair>

namespace GluonInput
{
    class InputDevice;

    class CustomInputPrivate : public QSharedData
    {
        public:
            CustomInputPrivate();
            CustomInputPrivate(CustomInputPrivate &other);
            ~CustomInputPrivate();

            QMap <QString, QPair<InputDevice*, int> > m_buttons;
            QMap <QString, QPair<InputDevice*, int> > m_absAxis;
            QMap <QString, QPair<InputDevice*, int> > m_relAxis;
    };

}
#endif
