#include "code.h"

#include <QtCore/QVariant>

namespace GluonInput
{
    const QString GLUONINPUT_CODE_BUTTON[GLUONINPUT_CODE_BUTTON_SIZE] =  {"Reserved", "Reserved", "Reserved", "Reserved", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
            "Return", "ESCAPE", "DELETE", "Tab", "Spacebar", "-", "=", "[", "]", "\"", "Non-US # and ~", ";", "'", "Grave Accent and Tilde", ",", ".", "/", "Caps Lock",
            "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
            "PrintScreen", "Scroll", "Pause", "Insert", "Home", "PageUp", "Delete Forward", "End", "PageDown",
            "RightArrow", "LeftArrow", "DownArrow", "UpArrow",
            "Keypad Num Lock and Clear", "Keypad /", "Keypad *", "Keypad -", "Keypad +", "Keypad ENTER", "Keypad 1", "Keypad 2", "Keypad 3", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad 7", "Keypad 8", "Keypad 9", "Keypad 0", "Keypad . and Delete",
            "Non-US \\ and |", "Application", "Power", "Keypad =",
            "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
            "Execute", "Help", "Menu", "Select", "Stop", "Again", "Undo", "Cut", "Copy", "Paste", "Find", "Mute", "Volume Up", "Volume Down",
            "Locking Caps Lock", "Locking Num Lock", "Locking Scroll Lock",
            "Keypad Comma", "Keypad Equal Sign", "International1", "International2", "International3", "International4", "International5",
            "International6", "International7", "International8", "International9", "LANG1", "LANG2", "LANG3", "LANG4", "LANG5", "LANG6", "LANG7", "LANG8", "LANG9", "Alternate Erase", "SysReq/Attention", "Cancel", "Clear", "Prior", "Return", "Separator", "Out",
            "Oper", "Clear/Again", "CrSel/Props", "ExSel", "Reserved", "Keypad 00", "Keypad 000", "Thousands Separator", "Decimal Separator", "Currency Unit", "Currency Sub-unit", "Keypad (", "Keypad )", "Keypad {", "Keypad }", "Tab", "Backspace", "Keypad A", "Keypad B", "Keypad C", "Keypad D", "Keypad E", "Keypad F", "Keypad XOR", "Keypad ^", "Keypad %", "Keypad <", "Keypad >", "Keypad &", "Keypad &&", "Keypad |", "Keypad ||", "Keypad :", "Keypad #", "Keypad Space", "Keypad @", "Keypad !", "Keypad Memory Store", "Keypad Memory Recall", "Keypad Memory Clear", "Keypad Memory Add", "Keypad Memory Subtract", "Keypad Memory Multiply", "Keypad Memory Divide", "Keypad +/-", "Keypad Clear", "Keypad Clear Entry", "Keypad Binary", "Keypad Octal", "Keypad Decimal", "Keypad Hexadecimal",
            "Reserved", "Reserved", //Reserved
            "LeftControl", "LeftShift", "LeftAlt", "Left GUI", "RightControl", "RightShift", "RightAlt", "Right GUI"
                                                                         };


    const QString GLUONINPUT_CODE_RELABS[GLUONINPUT_CODE_RELABS_SIZE] = {   "Misc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*0-10*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*11-20*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*21-30*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*31-40*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, "X", "Y", "Z",/*41-50*/
            "Rx", "Ry", "Rz", NULL, "Dial", "Wheel", "Hat switch", NULL, NULL, NULL,/*51-60*/
            "XTilt", "YTilt", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*61-70*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*71-80*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*81-90*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*91-100*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*101-110*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*111-120*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*121-130*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*131-140*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*141-150*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*151-160*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*161-170*/
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,/*171-180*/
            NULL, NULL, NULL, NULL, NULL, "Rudder", "Throttle", NULL, NULL, NULL,/*181-190*/
            NULL, NULL, NULL, NULL, NULL, "Gas", "Brake"/*191-197*/
                                                                        };

    QString Code::buttonName(int code)
    {
        if (code > GLUONINPUT_CODE_BUTTON_SIZE - 1)
        {
            return "Button " + QVariant(code - GLUONINPUT_CODE_BUTTON_SIZE).toString();
        }
        else
        {
            return QString(GLUONINPUT_CODE_BUTTON[code]);
        }
    }

    QString Code::relAxisName(int code)
    {
        if (code > GLUONINPUT_CODE_RELABS_SIZE - 1)
        {
            return "";
        }
        else
        {
            return QString(GLUONINPUT_CODE_RELABS[code]);
        }
    }
    QString Code::absAxisName(int code)
    {
        if (code > GLUONINPUT_CODE_RELABS_SIZE - 1)
        {
            return "";
        }
        else
        {
            return QString(GLUONINPUT_CODE_RELABS[code]);
        }
    }
}
