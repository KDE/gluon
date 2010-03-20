#include "code.h"

#include <linux/input.h>
#include <linux/version.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <QtCore/QString>

namespace GluonInput
{
    const char *GLUONINPUT_CODE_EVENT[EV_MAX + 1] = { "Reset", "Key", "Relative", "Absolute", "MSC", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, "LED", "Sound", NULL, "Repeat", "ForceFeedback", "Power", "ForceFeedbackStatus"
                                                    };

    const char *GLUONINPUT_CODE_BUTTON[KEY_MAX + 1] = { "Reserved", "Esc", /* 0, 1 */
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", /* 2 - 11 */
            "Minus", "Equal", "Backspace", "Tab", /* 12 - 15 */
            "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", /* 16 - 25 */
            "LeftBrace", "RightBrace", "Enter", "LeftControl", /* 26 - 29 */
            "A", "S", "D", "F", "G", "H", "J", "K", "L", /* 30 - 38 */
            "Semicolon", "Apostrophe", "Grave", "LeftShift", "BackSlash", /* 39 - 43 */
            "Z", "X", "C", "V", "B", "N", "M",  /* 44 - 50 */
            "Comma", "Dot", "Slash", "RightShift", "KPAsterisk",
            "LeftAlt", "Space", "CapsLock",  /* 51 - 58 */
            "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", /* 59 - 68 */
            "NumLock", "ScrollLock", /* 69, 70 */
            "KP7", "KP8", "KP9", "KPMinus", /* 71 - 74 */
            "KP4", "KP5", "KP6", "KPPlus", /* 75 - 78 */
            "KP1", "KP2", "KP3", "KP0", "KPDot", /* 79 - 83 */
            NULL,
            "ZENKAKUHANKAKU", /* 85 */
            "102nd", "F11", "F12", /* 86 - 88 */
            "R0", "KATAKANA", "HIRAGANA", "HENKAN", /* 89 - 92 */
            "KATAKANAHIRAGANA", "MUHENKAN", "KPJPCOMMA", /* 93 - 95 */
            "KPEnter", "RightCtrl", "KPSlash", "SysRq", /* 96 - 99 */
            "RightAlt", "LineFeed", /*100 - 101 */
            "Home", "Up", "PageUp", "Left", "Right", "End", "Down",
            "PageDown", "Insert", "Delete", /* 102 - 111 */
            "Macro", "Mute", "VolumeDown", "VolumeUp", "Power", /* 112 - 116 */
            "KPEqual", "KPPlusMinus", "Pause", /* 117 - 119 */
            NULL,
            "KPComma", /* 121 */
            "Hanguel", "Hanja", "Yen", /* 122 - 124 */
            "LeftMeta", "RightMeta", "Compose", /* 125 - 127 */
            "Stop", "Again", "Props", "Undo", "Front", "Copy", "Open",
            "Paste", "Find", "Cut", "Help", "Menu", "Calc", "Setup",
            "Sleep", "WakeUp", "File", "SendFile", "DeleteFile", "X-fer",
            "Prog1", "Prog2", "WWW", "MSDOS", "Coffee", "Direction",
            "CycleWindows", "Mail", "Bookmarks", "Computer",
            "Back", "Forward", "CloseCD", "EjectCD", "EjectCloseCD",
            "NextSong", "PlayPause", "PreviousSong", "StopCD",
            "Record", "Rewind", "Phone", /* 128 - 169 */
            "ISOKey", "Config", "HomePage", "Refresh", "Exit",
            "Move", "Edit", "ScrollUp", "ScrollDown", /* 170 - 178 */
            "KPLeftParenthesis", "KPRightParenthesis", /* 179 - 180 */
            NULL, NULL,
            "F13", "F14", "F15", "F16", "F17", "F18",
            "F19", "F20", "F21", "F22", "F23", "F24", /* 183 - 194 */
            NULL, NULL, NULL, NULL, NULL,
            "PlayCD", "PauseCD", "Prog3", "Prog4", NULL,
            "Suspend", "Close", /* 200 - 206 */
            "Play", "FastForward", "BassBoost", "Print", "HP", "Camera",
            "Sound", "Question", "Email", "Chat", "Search",
            "Connect", "Finance", "Sport", "Shop", "AltErase",
            "Cancel", "BrightnessDown", "BrightnessUp", "Media", /* 207 - 226 */
            "SwitchVideoMode",
            "KBDIllumToggle", "KBDIllumDown", "KBDIllumUp", /* 227 - 230 */
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "Unknown", /* 240 */
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "Btn0", "Btn1", "Btn2", "Btn3", "Btn4",
            "Btn5", "Btn6", "Btn7", "Btn8", "Btn9", /* 256 - 265 */
            NULL, NULL, NULL, NULL, NULL, NULL,
            "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn",
            "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", /* 0x110 - 0x117 */
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn",
            "TopBtn2", "PinkieBtn", "BaseBtn", "BaseBtn2",
            "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6",
            NULL, NULL, NULL, "BtnDead", /* 0x120 - 0x12f */
            "BtnA", "BtnB", "BtnC", "BtnX",
            "BtnY", "BtnZ", "BtnTL", "BtnTR",
            "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart",
            "BtnMode", "BtnThumbL", "BtnThumbR", /* 0x130 - 0x13e */ NULL,
            "ToolPen", "ToolRubber", "ToolBrush", "ToolPencil",
            "ToolAirbrush", "ToolFinger", "ToolMouse", "ToolLens", /* 0x140-0x147 */
            NULL, NULL, "Touch", "Stylus",
            "Stylus2", "DoubleTap", "TripleTap", /* 0x14a - 0x14e */ NULL,
            "GearUp", "GearDown", /* 0x150, 0x151 */
            NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "Ok", "Select", "Goto", "Clear", "Power2", "Option", "Info", "Time",
            "Vendor", "Archive", "Program", "Channel",
            "Favorites", "Epg", "Pvr", "Mhp",
            "Language", "Title", "Subtitle", "Angle",
            "Zoom", "Mode", "Keyboard", "Screen",
            "Pc", "Tv", "Tv2", "Vcr", "Vcr2", "Sat", "Sat2", "Cd",
            "Tape", "Radio", "Tuner", "Player", "Text", "Dvd", "Aux", "Mp3",
            "Audio", "Video", "Directory", "List",
            "Memo", "Calendar", "Red", "Green",
            "Yellow", "Blue", "Channelup", "Channeldown",
            "First", "Last", "Ab", "Next",
            "Restart", "Slow", "Shuffle", "Break",
            "Previous", "Digits", "Teen", "Twen", /* 160 - 19f */
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "DelEol", "DelEos", "InsLine", "DelLine", /* 1c0 - 1c3 */
            NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "FN", "FN_ESC",
            "FN_F1", "FN_F2", "FN_F3", "FN_F4", "FN_F5",
            "FN_F6", "FN_F7", "FN_F8", "FN_F9", "FN_F10",
            "FN_F11", "FN_F12",
            "FN_1", "FN_2", "FN_D", "FN_E", "FN_F", "FN_S", "FN_B" /* 0x1d0 - 0x1e4 */
                                                      };


    const char *GLUONINPUT_CODE_RELATIV[REL_MAX + 1] = { "X", "Y", "Z", NULL,
            NULL, NULL, "HWheel", "Dial",
            /* 0x08: */ "Wheel", "MISC"
                                                       };


    const char *GLUONINPUT_CODE_ABSOLU[ABS_MAX + 1] = { "X", "Y", "Z", "Rx",  "Ry", "Rz", "Throttle", "Rudder",
            "Wheel", "Gas", "Brake", NULL, NULL, NULL, NULL, NULL,
            /* 0x10: */ "Hat0X", "Hat0Y", "Hat1X", "Hat1Y",
            "Hat2X", "Hat2Y", "Hat3X", "Hat 3Y",
            "Pressure", "Distance", "XTilt", "YTilt",
            "ToolWidth", NULL, NULL, NULL,
            /* 0x20: */ "Volume", NULL, NULL, NULL,
            NULL, NULL, NULL, NULL,
            /* 0x28: */ "Misc"
                                                      };

    QString Code::buttonName(int code)
    {
        return QString(GLUONINPUT_CODE_BUTTON[code]);
    }

    QString Code::relAxisName(int code)
    {
        return QString(GLUONINPUT_CODE_RELATIV[code]);
    }

    QString Code::absAxisName(int code)
    {
        return QString(GLUONINPUT_CODE_ABSOLU[code]);
    }

    QIcon Code::iconDevice(GluonInput::DeviceFlag device)
    {
        QIcon icon;
        switch (device)
        {
            case GluonInput::KeyBoardDevice:
                icon = QIcon("input-keyboard");
                break;
            case GluonInput::MouseDevice:
                icon = QIcon("input-mouse.png");
                break;
            case GluonInput::TouchpadDevice:
                icon = QIcon("input-mouse.png");
                break;
            case GluonInput::JoystickDevice:
                icon =  QIcon("input-gaming.png");
                break;
            case GluonInput::TabletDevice:
                icon = QIcon("input-tablet.png");
                break;
            case GluonInput::UnknownDevice:
                icon = QIcon("system-help.png");
                break;
            default:
                icon = QIcon("document.png");
                break;
        }

        return icon;
    }
}