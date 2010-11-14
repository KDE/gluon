#include "inputeventtextedit.h"

InputEventTextEdit::InputEventTextEdit(QTextEdit *parent)
    : QTextEdit(parent)
{
}

InputEventTextEdit::~InputEventTextEdit()
{
}

void InputEventTextEdit::keyPressEvent(QKeyEvent *event)
{
    append(event->text() + " is pressed");
}

void InputEventTextEdit::keyReleaseEvent(QKeyEvent *event)
{
    append(event->text() + " is released");
}

void InputEventTextEdit::mousePressEvent(QMouseEvent *event)
{
}

void InputEventTextEdit::mouseReleaseEvent(QMouseEvent *event)
{
}

void InputEventTextEdit::mouseMoveEvent(QMouseEvent *event)
{
}

void InputEventTextEdit::moveEvent(QMoveEvent *event)
{
}

#include "inputeventtextedit.moc"
