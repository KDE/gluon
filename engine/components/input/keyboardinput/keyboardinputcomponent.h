/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef KEYBOARDINPUTCOMPONENT_H
#define KEYBOARDINPUTCOMPONENT_H

#include "component.h"

#include "gluonbuttons.h"

namespace GluonInput
{
    class Keyboard;
}

namespace GluonEngine
{
    class KeyboardInputComponent : public Component
    {
            Q_OBJECT;
            GLUON_OBJECT( GluonEngine::KeyboardInputComponent )
            Q_PROPERTY( KeyName keyCode READ keyCode WRITE setKeyCode );
            Q_INTERFACES( GluonEngine::Component )
            Q_ENUMS( KeyName )

        public:
            enum KeyName
            {
                UNKNOWN,
                ESC,
                ONE,
                TWO,
                THREE,
                FOUR,
                FIVE,
                SIX,
                SEVEN,
                EIGHT,
                NINE, /*10*/
                ZERO,
                MINUS,
                EQUAL,
                BACKSPACE,
                TAB,
                Q,
                W,
                E,
                R,
                T, //20
                Y,
                U,
                I,
                O,
                P,
                LEFT_BRACKET,
                RIGHT_BRACKET,
                ENTER,
                LEFT_CONTROL,
                A, //30
                S,
                D,
                F,
                G,
                H,
                J,
                K,
                L,
                SEMICOLON,
                APOSTROPHE, //40
                GRAVE,
                LEFT_SHIFT,
                BACKSLASH,
                Z,
                X,
                C,
                V,
                B,
                N,
                M, //50
                COMMA,
                PUNCTUATION,
                SLASH,
                RIGHT_SHIFT,
                KEYPAD_ASTERISK,
                LEFT_ALT,
                SPACE,
                CAPSLOCK,
                F_ONE,
                F_TWO, //60
                F_THREE,
                F_FOUR,
                F_FIVE,
                F_SIX,
                F_SEVEN,
                F_EIGHT,
                F_NINE,
                F_TEN,
                NUM_LOCK,
                SCROLL_LOCK, //70
                KEYPAD_SEVEN,
                KEYPAD_EIGHT,
                KEYPAD_NINE,
                KEYPAD_MINUSE,
                KEYPAD_FOUR,
                KEYPAD_FIVE,
                KEYPAD_SIX,
                KEYPAD_PLUS,
                KEYPAD_ONE,
                KEYPAD_TWO, //80
                KEYPAD_THREE,
                KEYPAD_ZERO,
                KEYPAD_PUNCTUATION, /* 79 - 83 */
                KEY_UNUSED_0,
                ZENKAKUHANKAKU = 85,
                ONEZEROTWOND,
                F_ELEVEN,
                F_TWELVE,
                R_ZERO,
                KATAKANA, //90
                HIRAGANA,
                HENKAN,
                KATAKANAHIRAGANA,
                MUHENKAN,
                KEYPAD_JPCOMMA,
                KEYPAD_ENTER,
                RIGHT_CTRL,
                KEYPAD_SLASH,
                SYSRQ,
                RIGHT_ALT, //100
                LINEFEED,
                HOME,
                UP_ARROW,
                PAGEUP,
                LEFT_ARROW,
                RIGHT_ARROW,
                END,
                DOWN_ARROW,
                PAGEDOWN,
                INSERT, //110
                DELETE,
                MACRO,
                MUTE,
                VOLUME_DOWN,
                VOLUME_UP,
                POWER,
                KEYPAD_EQUAL,
                KEYPAD_PLUS_AND_MINUS,
                PAUSE,
                KEY_UNUSED_1, //120
                KEYPAD_COMMA = 121,
                HANGUEL,
                HANJA,
                YEN,
                LEFT_META,
                RIGHT_META,
                COMPOSE,
                STOP,
                AGAIN,
                PROPS,
                UNDO, //130
                FRONT,
                COPY,
                OPEN,
                PASTE,
                FIND,
                CUT,
                HELP,
                MENU,
                CALC,
                SETUP, //140
                SLEEP,
                WAKEUP,
                FILE,
                SEND_FILE,
                DELETE_FILE,
                X_FER,
                PROG_ONE,
                PROG_TWO,
                WWW,
                MSDOS, //150
                COFFEE,
                DIRECTION,
                CYCLE_WINDOWS,
                MAIL,
                BOOKMARKS,
                COMPUTER,
                BACK,
                FORWARD,
                CLOSE_CD,
                EJECT_CD, //160
                EJECT_AND_CLOSE_CD,
                NEXT_SONG,
                PLAY_PAUSE,
                PREVIOUS_SONG,
                STOP_CD,
                RECORD,
                REWIND,
                PHONE,
                ISOKEY,
                CONFIG, //170
                HOMEPAGE,
                REFRESH,
                EXIT,
                MOVE,
                EDIT,
                SCROLLUP,
                SCROLLDOWN,
                KEYPAD_LEFT_PARENTHESE,
                KEYPAD_RIGHT_PARENTHESE,
                KEY_UNUSED_2, //180
                KEY_UNUSED_3,
                KEY_UNUSED_4,
                KEY_UNUSED_5,
                F_THIRTEEN = 183,
                F_FOURTEEN,
                F_FIFTEEN,
                F_SIXTEEN,
                F_SEVENTEEN,
                F_EIGHTTEEN,
                F_NINETEEN, //190
                F_TWENTY,
                F_TWENTYONE,
                F_TWENTYTWO,
                F_TWENTYTHREE,
                F_TWENTYFOUR,
                KEY_UNUSED_6,
                KEY_UNUSED_7,
                KEY_UNUSED_8,
                KEY_UNUSED_9,
                PLAY_CD = 200, //200
                PAUSE_CD,
                PROG_THREE,
                PROG_FOUR,
                KEY_UNUSED_10,
                SUSPEND = 205,
                CLOSE,
                PLAY,
                FASTFORWARD,
                BASS_BOOST,
                PRINT, //210
                HP,
                CAMERA,
                SOUND,
                QUESTION,
                EMAIL,
                CHAT,
                SEARCH,
                CONNECT,
                FINANCE,
                SPORT,
                SHOP,
                ALT_ERASE,
                CANCEL,
                BRIGHTNESS_DOWN,
                BRIGHTNESS_UP,
                MEDIA,
                SWITCH_VIDEOMODE,
                KB_ILLUM_TOGGLE,
                KB_ILLUM_DOWN,
                KB_ILLUM_UP,
                BUTTON_ZERO = 256,
                BUTTON_ONE,
                BUTTON_TWO,
                BUTTON_THREE,
                BUTTON_FOUR,
                BUTTON_FIVE,
                BUTTON_SIX,
                BUTTON_SEVEN,
                BUTTON_EIGHT,
                BUTTON_NINE,
                MOUSE_LEFT_BUTTON = 272,
                MOUSE_RIGHT_BUTTON,
                MOUSE_MIDDLE_BUTTON,
                MOUSE_BUTTON_FOUR,
                MOUSE_BUTTON_FIVE,
                MOUSE_BUTTON_SIX,
                MOUSE_BUTTON_SEVEN,
                MOUSE_BUTTON_EIGHT,
                TRIGGER = 288,
                THUMB_BUTTON_ONE,
                THUMB_BUTTON_TWO,
                TOP_BUTTON_ONE,
                TOP_BUTTON_TWO,
                PINKIE_BUTTON,
                BASE_BUTTON_ONE,
                BASE_BUTTON_TWO,
                BASE_BUTTON_THREE,
                BASE_BUTTON_FOUR,
                BASE_BUTTON_FIVE,
                BASE_BUTTON_SIX,
                BUTTON_DEAD = 303,
                BUTTON_A,
                BUTTON_B,
                BUTTON_C,
                BUTTON_X,
                BUTTON_Y,
                BUTTON_Z,
                BUTTON_TL_ONE,
                BUTTON_TR_ONE,
                BUTTON_TL_TWO,
                BUTTON_TR_TWO,
                BUTTON_SELECT,
                BUTTON_START,
                BUTTON_MODE,
                BUTTON_THUMB_LEFT,
                BUTTON_THUMB_RIGHT,
                TOOL_PEN = 320,
                TOOL_RUBBER,
                TOOL_BRUSH,
                TOOL_PENCIL,
                TOOL_AIRBRUSH,
                TOOL_FINGER,
                TOOL_MOUSE,
                TOOL_LENS,
                TOUCH = 330,
                STYLUS,
                STYLUS_TWO,
                DOUBLETAB,
                TRIPLETAB,
                GEAR_UP = 336,
                GEAR_DOWN,
                OK = 352,
                SELECT,
                GOTO,
                CLEAR,
                POWER_TWO,
                OPTION,
                INFO,
                TIME,
                VENDOR,
                ARCHIVE,
                PROGRAM,
                CHANNEL,
                FAVORITES,
                EPG,
                PVR,
                MHP,
                LANGUAGE,
                TITLE,
                SUBTITLE,
                ANGLE,
                ZOOM,
                MODE,
                KEYBOARD,
                SCREEN,
                PC,
                TV,
                TV_TWO,
                VCR,
                VCR_TWO,
                SAT,
                SAT_TWO,
                CD,
                TAPE,
                RADIO,
                TUNER,
                PLAYER,
                TEXT,
                DVD,
                AUX,
                MP_THREE,
                AUDIO,
                VIDEO,
                DIRECTORY,
                LIST,
                MEMO,
                CALENDAR,
                RED,
                GREEN,
                YELLOW,
                BLUE,
                CHANNEL_UP,
                CHANNEL_DOWN,
                FIRST,
                LAST,
                AB,
                NEXT,
                RESTART,
                SLOW,
                SHUFFLE,
                BREAK,
                PREVIOUS,
                DIGITS,
                TEEN,
                TWEN,
                DELEOL = 448,
                DELEOS,
                INSLINE,
                DELLINE,
                FN = 464,
                FN_ESC,
                FN_F_ONE,
                FN_F_TWO,
                FN_F_THREE,
                FN_F_FOUR,
                FN_F_FIVE,
                FN_F_SIX,
                FN_F_SEVEN,
                FN_F_EIGHT,
                FN_F_NINE,
                FN_F_TEN,
                FN_F_ELEVEN,
                FN_F_TWELVE,
                FN_ONE,
                FN_TWO,
                FN_D,
                FN_E,
                FN_F,
                FN_S,
                FN_B
            };

            Q_INVOKABLE KeyboardInputComponent( QObject* parent = 0 );
            virtual QString category() const;

            // True on any frame between getActionStarted and
            // getActionStopped, inclusive of those two frames
            Q_INVOKABLE bool isActionHeld();
            // True on the frame when an action was begun (for example the
            // button represented by buttonName was pressed on a controller)
            Q_INVOKABLE bool isActionStarted();
            // True on the frame when an action was stopped (for example a
            // button was released on a controller)
            Q_INVOKABLE bool isActionStopped();

            virtual void initialize();
            virtual void start();
            virtual void update( int elapsedMilliseconds );
            virtual void stop();

            KeyName keyCode() const;
            void setKeyCode( KeyName newKeyCode );

        private:
            bool m_actionHeld;
            bool m_actionStarted;
            bool m_actionStopped;

            KeyName m_keyCode;

            GluonInput::Keyboard* m_keyboard;
    };
}

Q_DECLARE_METATYPE( GluonEngine::KeyboardInputComponent )
Q_DECLARE_METATYPE( GluonEngine::KeyboardInputComponent* )

#endif // KEYBOARDINPUTCOMPONENT_H
