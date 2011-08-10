/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUON_INPUT_GLUONBUTTONS_H
#define GLUON_INPUT_GLUONBUTTONS_H

#include "gluon_input_export.h"
#include "gluondevices.h"

#include <core/singleton.h>

namespace GluonInput
{
    class GluonButtons : public GluonCore::Singleton<GluonButtons>
    {
            Q_OBJECT
            Q_ENUMS( KeyboardButton )
            Q_ENUMS( JoystickButton )
            Q_ENUMS( MouseButton )
            Q_ENUMS( RelAbs )
            GLUON_SINGLETON( GluonButtons )

        public:
            enum KeyboardButton
            {
                A = 4,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                M,
                N,
                O,
                P,
                Q,
                R,
                S,
                T,
                U,
                V,
                W,
                X,
                Y,
                Z,
                ONE,
                TWO,
                THREE,
                FOUR,
                FIVE,
                SIX,
                SEVEN,
                EIGHT,
                NINE,
                ZERO,
                RETURN,
                ESC,
                DEL,
                TAB,
                SPACE,
                MINUS,
                EQUAL,
                LEFT_BRACKET,
                RIGHT_BRACKET,
                QUOTE,
                NON_US_HASH_AND_TILDE,
                SEMICOLON,
                APOSTROPHE,
                GRAVE_ACCENT_ANF_TILDE,
                COMMA,
                PUNCTUATION,
                SLASH,
                CAPS_LOCK,
                F_ONE,
                F_TWO,
                F_THREE,
                F_FOUR,
                F_FIVE,
                F_SIX,
                F_SEVEN,
                F_EIGHT,
                F_NINE,
                F_TEN,
                F_ELEVEN,
                F_TWELVE,
                PRINTSCREEN,
                SCROLL,
                PAUSE,
                INSERT,
                HOME,
                PAGEUP,
                DELETE_FORWARD,
                END,
                PAGEDOWN,
                RIGHT_ARROW,
                LEFT_ARROW,
                DOWN_ARROW,
                UP_ARROW,
                KEYPAD_NUM_LOCK_AND_CLEAR,
                Keypad_SLASH,
                KEYPARD_STAR,
                KEYPAD_MINUS,
                KEYPAD_PLUS,
                KEYPAD_ENTER,
                KEYPAD_ONE,
                KEYPAD_TWO,
                KEYPAD_THREE,
                KEYPAD_FOUR,
                KEYPAD_FIVE,
                KEYPAD_SIX,
                KEYPAD_SEVEN,
                KEYPAD_EIGHT,
                KEYPAD_NINE,
                KEYPAD_ZERO,
                KEYPAD_PUNCTUATION_AND_DELETE,
                NON_US_BACKSLASH_AND_PIPE,
                APPLICATION,
                POWER,
                KEYPAD_EQUAL,
                F_THIRTEEN,
                F_FOURTEEN,
                F_FIFTEEN,
                F_SIXTEEN,
                F_SEVENTEEN,
                F_EIGHTTEEN,
                F_NINETEEN,
                F_TWENTY,
                F_TWENTYONE,
                F_TWENTYTWO,
                F_TWENTYTHREE,
                F_TWENTYFOUR,
                EXECUTE,
                HELP,
                MENU,
                SELECT,
                STOP,
                AGAIN,
                UNDO,
                CUT,
                COPY,
                PASTE,
                FIND,
                MUTE,
                VOLUME_UP,
                VOLUME_DOWN,
                LOCKING_CAPS_LOCK,
                LOCKING_NUM_LOCK,
                LOCKING_SCROLL_LOCK,
                KEYPAD_COMMA,
                KEYPAD_EQUAL_SIGN,
                INTERNATIONAL_ONE,
                INTERNATIONAL_TWO,
                INTERNATIONAL_THREE,
                INTERNATIONAL_FOUR,
                INTERNATIONAL_FIVE,
                INTERNATIONAL_SIX,
                INTERNATIONAL_SEVEN,
                INTERNATIONAL_EIGHT,
                INTERNATIONAL_NINE,
                LANG_ONE,
                LANG_TWO,
                LANG_THREE,
                LANG_FOUR,
                LANG_FIVE,
                LANG_SIX,
                LANG_SEVEN,
                LANG_EIGHT,
                LANG_NINE,
                ALTERNATE_ERASE,
                SYSREG_AND_ATTENTION,
                CANCEL,
                CLEAR,
                PROPR,
                RETURN_SECOND,
                SEPARATOR,
                OUT,
                OPER,
                CLEAR_AND_AGAIN,
                CRSEL_AND_PROPS,
                EXSEL,
                KEYPAD_ZEROZERO = 176,
                KEYPAD_ZEROZEROZERO,
                THOUSANDS_SEPARATOR,
                DECIMAL_SEPARATOR,
                CURRENCY_UNIT,
                CURRENCY_SUBUNIT,
                KEYPAD_LEFT_PARENTHESE,
                KEYPAD_RIGHT_PARENTHESE,
                KEYPAD_LEFT_CURLY_BRACKET,
                KEYPAD_RIGHT_CURLY_BRACKET,
                TAB_SECOND,
                BACKSPACE,
                KEYPAD_A,
                KEYPAD_B,
                KEYPAD_C,
                KEYPAD_D,
                KEYPAD_E,
                KEYPAD_F,
                KEYPAD_XOR,
                KEYPAD_CARET,
                KEYPAD_PROCENT,
                KEYPAD_LESSTHAN,
                KEYPAD_GREATERTHAN,
                KEYPAD_AMPERSAND,
                KEYPAD_AMPERSANDAMPERSAND,
                KEYPAD_PIPE,
                KEYPAD_PIPEPIPE,
                KEYPAD_COLON,
                KEYPAD_HASH,
                KEYPAD_SPACE,
                KEYPAD_AT,
                KEYPAD_EXCLAMATION_MARK,
                KEYPAD_MEMORY_STORE,
                KEYPAD_MEMORY_RECALL,
                KEYPAD_MEMORY_CLEAR,
                KEYPAD_MEMORY_ADD,
                KEYPAD_MEMORY_SUBTRACT,
                KEYPAD_MEMORY_MULTIPLY,
                KEYPAD_MEMORY_DIVIDE,
                KEYPAD_PLUS_AND_MINUS,
                KEYPAD_CLEAR,
                KEYPAD_CLEAR_ENTRY,
                KEYPAD_BINARY,
                KEYPAD_OCTAL,
                KEYPAD_DECIMAL,
                KEYPAD_HEXADECIMAL,
                LEFT_CTRL = 224,
                LEFT_SHIFT,
                LEFT_ALT,
                LEFT_GUI,
                RIGHT_CTRL,
                RIGHT_SHIFT,
                RIGHT_ALT,
                RIGHT_GUI
            };

            enum RelAbs
            {
                HWHEEL = -1, //I do not know how HID is handling this
                MISC = 0,
                X_REL = 48,
                Y_REL = 49,
                Z_REL = 50,
                X_ABS = 48,
                Y_ABS = 49,
                Z_ABS = 50,
                ROTATION_X_AXIS,
                ROTATION_Y_AXIS,
                ROTATION_Z_AXIS,
                DIAL = 55,
                WHEEL_REL,
                HAT_SWITCH,
                XTILT = 61,
                YTILT,
                RUDDER = 186,
                THROTTLE,
                GAS = 196,
                BRAKE
            };

            enum MouseButton
            {
                MOUSE_LEFT_BUTTON = 1,
                MOUSE_RIGHT_BUTTON,
                MOUSE_MIDDLE_BUTTON,
                MOUSE_BUTTON_FOUR,
                MOUSE_BUTTON_FIVE,
                MOUSE_BUTTON_SIX,
                MOUSE_BUTTON_SEVEN,
                MOUSE_BUTTON_EIGHT,
            };

            enum JoystickButton
            {
                BUTTON_ONE = 1,
                BUTTON_TWO,
                BUTTON_THREE,
                BUTTON_FOUR,
                BUTTON_FIVE,
                BUTTON_SIX,
                BUTTON_SEVEN,
                BUTTON_EIGHT,
                BUTTON_NINE
            };

            QString buttonName( DeviceFlag deviceType, int code );
            QString axisName( DeviceFlag deviceType, int code );

        private:
            ~GluonButtons();

    };
}

#endif // GLUON_INPUT_GLUONBUTTONS_H
