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
    emit buttonStateChanged(event->nativeScanCode(), 1);
}

void InputEventTextEdit::keyReleaseEvent(QKeyEvent *event)
{
    emit buttonStateChanged(event->nativeScanCode(), 0);
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
