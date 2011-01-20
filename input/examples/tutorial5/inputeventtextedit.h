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

};

#endif // INPUTEVENTTEXTEDIT_H
