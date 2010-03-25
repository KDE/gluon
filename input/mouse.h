#ifndef MOUSE_H
#define MOUSE_H

#include "inputdevice.h"

#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QWidget>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputThread;
    class MousePrivate;

    class GLUON_INPUT_EXPORT Mouse : public InputDevice
    {
            Q_OBJECT

        public:
            Mouse(InputThread * inputThread, QObject * parent = 0);

            QPoint position();
            void setSensibility(double s);
            void setOrigin(const QPoint p);
            int wheelPosition() const;
            int hWheelPosition()const;
            double sensibility()const;
	   
      private slots:
	  void mouseMoved(int axis, int distance);
	    
        private:	    
            QSharedDataPointer<MousePrivate> d;
    };
}
//@}
#endif // KCLMOUSE_H
