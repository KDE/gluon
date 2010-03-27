#ifndef CUSTOMINPUT_H
#define CUSTOMINPUT_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QSharedData>

#include "gluon_input_export.h"
#include "gluondevices.h"

namespace GluonInput
{
    class InputDevice;
    class InputEvent;
    class CustomInputPrivate;

    class GLUON_INPUT_EXPORT CustomInput : public QObject
    {
            Q_OBJECT
        public:
            CustomInput(QObject * parent = 0);
            ~CustomInput();

            void setButton(const QString &name, InputDevice* input, int keyCode);
            void setButton(const QString &name);
            void remButton(const QString &name);
            void setAbsAxis(const QString &name, InputDevice * input, int axis);
            void setRelAxis(const QString &name, InputDevice* input, int axis);
            void remAbsAxis(const QString &name);
            void remRelAxis(const QString &name);

            QStringList buttonNameList();
            QStringList absAxisNameList();
            QStringList relAxisNameList();

        signals:
            void buttonPressed(QString name);
            void buttonReleased(QString name);
            void absAxisChanged(QString name, int value);
            void relAxisChanged(QString name, int value);

        private:
            QSharedDataPointer<CustomInputPrivate> d;
    };
}

#endif // KCLCUSTOMINPUT_H
