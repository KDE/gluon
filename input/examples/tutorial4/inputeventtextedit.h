#ifndef INPUTEVENTTEXTEDIT_H
#define INPUTEVENTTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMoveEvent>

class InputEventTextEdit : public QTextEdit
{
        Q_OBJECT
    public:
        explicit InputEventTextEdit( QTextEdit* parent = 0 );
        virtual ~InputEventTextEdit();

    protected:
        void keyPressEvent( QKeyEvent* event );
        void keyReleaseEvent( QKeyEvent* event );
        void mousePressEvent( QMouseEvent* event );
        void mouseReleaseEvent( QMouseEvent* event );
        void mouseMoveEvent( QMouseEvent* event );
        void moveEvent( QMoveEvent* event );

    signals:
        void buttonStateChanged( int code, int value );
};

#endif // INPUTEVENTTEXTEDIT_H
