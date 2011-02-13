/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "inputthread.h"
#include "absval.h"
#include "inputthreadprivate.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QEvent>
#include <QtCore/QStringList>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)

using namespace GluonInput;

InputThread::InputThread( const QString& devicePath, QObject* parent )
    : QThread( parent )
    , d( new InputThreadPrivate )
{
    d->m_devicePath = devicePath;
    if( openDevice( devicePath ) )
        readInformation();
}

// InputThread::InputThread(struct udev_device *dev, QObject *parent)
// : QThread(parent)
// , d(new InputThreadPrivate)
// {
// d->m_udevDevice = dev;
// readSystemFS();
// }

InputThread::~InputThread()
{
    closeDevice();
}

int InputThread::mapKeyCode(int keyCode)
{
    switch( keyCode )
    {
        case KEY_ESC:
            return Qt::Key_Escape;
        case KEY_1:
            return Qt::Key_1;
        case KEY_2:
            return Qt::Key_2;
        case KEY_3:
            return Qt::Key_3;
        case KEY_4:
            return Qt::Key_4;
        case KEY_5:
            return Qt::Key_5;
        case KEY_6:
            return Qt::Key_6;
        case KEY_7:
            return Qt::Key_7;
        case KEY_8:
            return Qt::Key_8;
        case KEY_9:
            return Qt::Key_9;
        case KEY_0:
            return Qt::Key_0;
        case KEY_MINUS:
            return Qt::Key_Minus;
        case KEY_EQUAL:
            return Qt::Key_Equal;
        case KEY_BACKSPACE:
            return Qt::Key_Backspace;
        case KEY_TAB:
            return Qt::Key_Tab;
        case KEY_Q:
            return Qt::Key_Q;
        case KEY_W:
            return Qt::Key_W;
        case KEY_E:
            return Qt::Key_E;
        case KEY_R:
            return Qt::Key_R;
        case KEY_T:
            return Qt::Key_T;
        case KEY_Y:
            return Qt::Key_Y;
        case KEY_U:
            return Qt::Key_U;
        case KEY_I:
            return Qt::Key_I;
        case KEY_O:
            return Qt::Key_O;
        case KEY_P:
            return Qt::Key_P;
        case KEY_LEFTBRACE:
            return Qt::Key_BraceLeft;
        case KEY_RIGHTBRACE:
            return Qt::Key_BraceRight;
        case KEY_ENTER:
            return Qt::Key_Return;
        case KEY_LEFTCTRL:
            return Qt::Key_Control;
        case KEY_A:
            return Qt::Key_A;
        case KEY_S:
            return Qt::Key_S;
        case KEY_D:
            return Qt::Key_D;
        case KEY_F:
            return Qt::Key_F;
        case KEY_G:
            return Qt::Key_G;
        case KEY_H:
            return Qt::Key_H;
        case KEY_J:
            return Qt::Key_J;
        case KEY_K:
            return Qt::Key_K;
        case KEY_L:
            return Qt::Key_L;
        case KEY_SEMICOLON:
            return Qt::Key_Semicolon;
        case KEY_APOSTROPHE:
            return Qt::Key_Apostrophe;
        case KEY_GRAVE:
            return Qt::Key_unknown; // ???
        case KEY_LEFTSHIFT:
            return Qt::Key_Shift;
        case KEY_BACKSLASH:
            return Qt::Key_Backslash;
        case KEY_Z:
            return Qt::Key_Z;
        case KEY_X:
            return Qt::Key_X;
        case KEY_C:
            return Qt::Key_C;
        case KEY_V:
            return Qt::Key_V;
        case KEY_B:
            return Qt::Key_B;
        case KEY_N:
            return Qt::Key_N;
        case KEY_M:
            return Qt::Key_M;
        case KEY_COMMA:
            return Qt::Key_Comma;
        case KEY_DOT:
            return Qt::Key_Period;
        case KEY_SLASH:
            return Qt::Key_Slash;
        case KEY_RIGHTSHIFT:
            return Qt::Key_Shift;
        case KEY_KPASTERISK:
            return Qt::Key_Asterisk;
        case KEY_LEFTALT:
            return Qt::Key_Alt;
        case KEY_SPACE:
            return Qt::Key_Space;
        case KEY_CAPSLOCK:
            return Qt::Key_CapsLock;
        case KEY_F1:
            return Qt::Key_F1;
        case KEY_F2:
            return Qt::Key_F2;
        case KEY_F3:
            return Qt::Key_F3;
        case KEY_F4:
            return Qt::Key_F4;
        case KEY_F5:
            return Qt::Key_F5;
        case KEY_F6:
            return Qt::Key_F6;
        case KEY_F7:
            return Qt::Key_F7;
        case KEY_F8:
            return Qt::Key_F8;
        case KEY_F9:
            return Qt::Key_F9;
        case KEY_F10:
            return Qt::Key_F10;
        case KEY_NUMLOCK:
            return Qt::Key_NumLock;
        case KEY_SCROLLLOCK:
            return Qt::Key_ScrollLock;
        case KEY_KP7:
            return Qt::Key_unknown;
        case KEY_KP8:
            return Qt::Key_unknown;
        case KEY_KP9:
            return Qt::Key_unknown;
        case KEY_KPMINUS:
            return Qt::Key_unknown;
        case KEY_KP4:
            return Qt::Key_unknown;
        case KEY_KP5:
            return Qt::Key_unknown;
        case KEY_KP6:
            return Qt::Key_unknown;
        case KEY_KPPLUS:
            return Qt::Key_unknown;
        case KEY_KP1:
            return Qt::Key_unknown;
        case KEY_KP2:
            return Qt::Key_unknown;
        case KEY_KP3:
            return Qt::Key_unknown;
        case KEY_KP0:
            return Qt::Key_unknown;
        case KEY_KPDOT:
            return Qt::Key_unknown;
        case KEY_ZENKAKUHANKAKU:
            return Qt::Key_Zenkaku_Hankaku;
        case KEY_102ND:
            return Qt::Key_unknown;
        case KEY_F11:
            return Qt::Key_F12;
        case KEY_F12:
            return Qt::Key_F12;
        case KEY_RO:
            return Qt::Key_unknown;
        case KEY_KATAKANA:
            return Qt::Key_Katakana;
        case KEY_HIRAGANA:
            return Qt::Key_Hiragana;
        case KEY_HENKAN:
            return Qt::Key_Henkan;
        case KEY_KATAKANAHIRAGANA:
            return Qt::Key_Hiragana_Katakana;
        case KEY_MUHENKAN:
            return Qt::Key_Muhenkan;
        case KEY_KPJPCOMMA:
            return Qt::Key_unknown;
        case KEY_KPENTER:
            return Qt::Key_Enter;
        case KEY_RIGHTCTRL:
            return Qt::Key_Control;
        case KEY_KPSLASH:
            return Qt::Key_unknown;
        case KEY_SYSRQ:
            return Qt::Key_SysReq;
        case KEY_RIGHTALT:
            return Qt::Key_AltGr;
        case KEY_LINEFEED:
            return Qt::Key_Return;
        case KEY_HOME:
            return Qt::Key_Home;
        case KEY_UP:
            return Qt::Key_Up;
        case KEY_PAGEUP:
            return Qt::Key_PageUp;
        case KEY_LEFT:
            return Qt::Key_Left;
        case KEY_RIGHT:
            return Qt::Key_Right;
        case KEY_END:
            return Qt::Key_End;
        case KEY_DOWN:
            return Qt::Key_Down;
        case KEY_PAGEDOWN:
            return Qt::Key_PageDown;
        case KEY_INSERT:
            return Qt::Key_Insert;
        case KEY_DELETE:
            return Qt::Key_Delete;
        case KEY_MACRO:
            return Qt::Key_unknown;
        case KEY_MUTE:
            return Qt::Key_VolumeMute;
        case KEY_VOLUMEDOWN:
            return Qt::Key_VolumeDown;
        case KEY_VOLUMEUP:
            return Qt::Key_VolumeUp;
        case KEY_POWER:       /* SC System Power Down */
            return Qt::Key_PowerDown;
        case KEY_KPEQUAL:
            return Qt::Key_unknown;
        case KEY_KPPLUSMINUS:
            return Qt::Key_unknown;
        case KEY_PAUSE:
            return Qt::Key_Pause;
        case KEY_SCALE:        /* AL Compiz Scale (Expose) */
            return Qt::Key_unknown;
        case KEY_KPCOMMA:
            return Qt::Key_unknown;
        case KEY_HANGEUL:
            return Qt::Key_unknown;
        // case KEY_HANGUEL:       - KEY_HANGEUL
            // return Qt::Key_unknown;
        case KEY_HANJA:
            return Qt::Key_Hangul_Hanja;
        case KEY_YEN:
            return Qt::Key_yen;
        case KEY_LEFTMETA:
            return Qt::Key_Meta;
        case KEY_RIGHTMETA:
            return Qt::Key_Meta;
        case KEY_COMPOSE:
            return Qt::Key_unknown;
        case KEY_STOP:        /* AC Stop */
            return Qt::Key_Stop;
        case KEY_AGAIN:
            return Qt::Key_unknown;
        case KEY_PROPS:       /* AC Properties */
            return Qt::Key_unknown;
        case KEY_UNDO:        /* AC Undo */
            return Qt::Key_unknown;
        case KEY_FRONT:
            return Qt::Key_unknown;
        case KEY_COPY:        /* AC Copy */
            return Qt::Key_Copy;
        case KEY_OPEN:        /* AC Open */
            return Qt::Key_unknown;
        case KEY_PASTE:       /* AC Paste */
            return Qt::Key_Paste;
        case KEY_FIND:        /* AC Search */
            return Qt::Key_unknown;
        case KEY_CUT:         /* AC Cut */
            return Qt::Key_Cut;
        case KEY_HELP:        /* AL Integrated Help Center */
            return Qt::Key_Help;
        case KEY_MENU:        /* Menu (show menu) */
            return Qt::Key_Menu;
        case KEY_CALC:        /* AL Calculator */
            return Qt::Key_Calculator;
        case KEY_SETUP:
            return Qt::Key_unknown;
        case KEY_SLEEP:       /* SC System Sleep */
            return Qt::Key_Sleep;
        case KEY_WAKEUP:      /* System Wake Up */
            return Qt::Key_WakeUp;
        case KEY_FILE:        /* AL Local Machine Browser */
            return Qt::Key_unknown;
        case KEY_SENDFILE:
            return Qt::Key_unknown;
        case KEY_DELETEFILE:
            return Qt::Key_unknown;
        case KEY_XFER:
            return Qt::Key_Xfer;
        case KEY_PROG1:
            return Qt::Key_unknown;
        case KEY_PROG2:
            return Qt::Key_unknown;
        case KEY_WWW:         /* AL Internet Browser */
            return Qt::Key_WWW;
        case KEY_MSDOS:
            return Qt::Key_DOS;
        case KEY_COFFEE:      /* AL Terminal Lock/Screensaver */
            return Qt::Key_unknown;
        // case KEY_SCREENLOCK:  - KEY_COFFEE
            // return Qt::Key_unknown;
        case KEY_DIRECTION:
            return Qt::Key_unknown;
        case KEY_CYCLEWINDOWS:
            return Qt::Key_unknown;
        case KEY_MAIL:
            return Qt::Key_LaunchMail;
        case KEY_BOOKMARKS:   /* AC Bookmarks */
            return Qt::Key_Book;
        case KEY_COMPUTER:
            return Qt::Key_unknown;
        case KEY_BACK:        /* AC Back */
            return Qt::Key_Back;
        case KEY_FORWARD:     /* AC Forward */
            return Qt::Key_Forward;
        case KEY_CLOSECD:
            return Qt::Key_Close;
        case KEY_EJECTCD:
            return Qt::Key_Eject;
        case KEY_EJECTCLOSECD:
            return Qt::Key_unknown;
        case KEY_NEXTSONG:
            return Qt::Key_MediaNext;
        case KEY_PLAYPAUSE:
            return Qt::Key_unknown;
        case KEY_PREVIOUSSONG:
            return Qt::Key_MediaPrevious;
        case KEY_STOPCD:
            return Qt::Key_unknown;
        case KEY_RECORD:
            return Qt::Key_MediaRecord;
        case KEY_REWIND:
            return Qt::Key_AudioRewind;
        case KEY_PHONE:        /* Media Select Telephone */
            return Qt::Key_Phone;
        case KEY_ISO:
            return Qt::Key_unknown;
        case KEY_CONFIG:       /* AL Consumer Control Configuration */
            return Qt::Key_unknown;
        case KEY_HOMEPAGE:     /* AC Home */
            return Qt::Key_HomePage;
        case KEY_REFRESH:      /* AC Refresh */
            return Qt::Key_Refresh;
        case KEY_EXIT:         /* AC Exit */
            return Qt::Key_unknown;
        case KEY_MOVE:
            return Qt::Key_unknown;
        case KEY_EDIT:
            return Qt::Key_unknown;
        case KEY_SCROLLUP:
            return Qt::Key_unknown;
        case KEY_SCROLLDOWN:
            return Qt::Key_unknown;
        case KEY_KPLEFTPAREN:
            return Qt::Key_unknown;
        case KEY_KPRIGHTPAREN:
            return Qt::Key_unknown;
        case KEY_NEW:         /* AC New */
            return Qt::Key_News;
        case KEY_REDO:        /* AC Redo/Repeat */
            return Qt::Key_unknown;
        case KEY_F13:
            return Qt::Key_F13;
        case KEY_F14:
            return Qt::Key_F14;
        case KEY_F15:
            return Qt::Key_F15;
        case KEY_F16:
            return Qt::Key_F16;
        case KEY_F17:
            return Qt::Key_F17;
        case KEY_F18:
            return Qt::Key_F18;
        case KEY_F19:
            return Qt::Key_F19;
        case KEY_F20:
            return Qt::Key_F20;
        case KEY_F21:
            return Qt::Key_F21;
        case KEY_F22:
            return Qt::Key_F22;
        case KEY_F23:
            return Qt::Key_F23;
        case KEY_F24:
            return Qt::Key_F24;
        case KEY_PLAYCD:
            return Qt::Key_unknown;
        case KEY_PAUSECD:
            return Qt::Key_unknown;
        case KEY_PROG3:
            return Qt::Key_unknown;
        case KEY_PROG4:
            return Qt::Key_unknown;
        case KEY_DASHBOARD:    /* AL Dashboard */
            return Qt::Key_unknown;
        case KEY_SUSPEND:
            return Qt::Key_Suspend;
        case KEY_CLOSE:       /* AC Close */
            return Qt::Key_Close;
        case KEY_PLAY:
            return Qt::Key_Play;
        case KEY_FASTFORWARD:
            return Qt::Key_unknown;
        case KEY_BASSBOOST:
            return Qt::Key_BassBoost;
        case KEY_PRINT:       /* AC Print */
            return Qt::Key_Print;
        case KEY_HP:
            return Qt::Key_unknown;
        case KEY_CAMERA:
            return Qt::Key_unknown;
        case KEY_SOUND:
            return Qt::Key_unknown;
        case KEY_QUESTION:
            return Qt::Key_Question;
        case KEY_EMAIL:
            return Qt::Key_unknown;
        case KEY_CHAT:
            return Qt::Key_unknown;
        case KEY_SEARCH:
            return Qt::Key_Search;
        case KEY_CONNECT:
            return Qt::Key_unknown;
        case KEY_FINANCE:     /* AL Checkbook/Finance */
            return Qt::Key_Finance;
        case KEY_SPORT:
            return Qt::Key_unknown;
        case KEY_SHOP:
            return Qt::Key_Shop;
        case KEY_ALTERASE:
            return Qt::Key_unknown;
        case KEY_CANCEL:      /* AC Cancel */
            return Qt::Key_Cancel;
        case KEY_BRIGHTNESSDOWN:
            return Qt::Key_KeyboardBrightnessDown;
        case KEY_BRIGHTNESSUP:
            return Qt::Key_KeyboardBrightnessUp;
        case KEY_MEDIA:
            return Qt::Key_LaunchMedia;
        case KEY_SWITCHVIDEOMODE:  /* Cycle between available video
                                       outputs (Monitor/LCD/TV-out/etc) */
            return Qt::Key_Mode_switch;
        case KEY_KBDILLUMTOGGLE:
            return Qt::Key_unknown;
        case KEY_KBDILLUMDOWN:
            return Qt::Key_unknown;
        case KEY_KBDILLUMUP:
            return Qt::Key_unknown;
        case KEY_SEND:         /* AC Send */
            return Qt::Key_Send;
        case KEY_REPLY:        /* AC Reply */
            return Qt::Key_Reply;
        case KEY_FORWARDMAIL:  /* AC Forward Msg */
            return Qt::Key_MailForward;
        case KEY_SAVE:         /* AC Save */
            return Qt::Key_Save;
        case KEY_DOCUMENTS:
            return Qt::Key_Documents;
        case KEY_BATTERY:
            return Qt::Key_Battery;
        case KEY_BLUETOOTH:
            return Qt::Key_Bluetooth;
        case KEY_WLAN:
            return Qt::Key_WLAN;
        case KEY_UWB:
            return Qt::Key_UWB;
        case KEY_UNKNOWN:
            return Qt::Key_unknown;
        case KEY_VIDEO_NEXT:       /* drive next video source */
            return Qt::Key_unknown;
        case KEY_VIDEO_PREV:       /* drive previous video source */
            return Qt::Key_unknown;
        case KEY_BRIGHTNESS_CYCLE: /* brightness up, after max is min */
            return Qt::Key_unknown;
        case KEY_BRIGHTNESS_ZERO:  /* brightness off, use ambient */
            return Qt::Key_unknown;
        case KEY_DISPLAY_OFF:      /* display device to off state */
            return Qt::Key_Display;
        case KEY_WIMAX:
            return Qt::Key_unknown;

        default:
            return Qt::Key_unknown;
    }
}

void InputThread::run()
{
    while( 1 )
    {
        struct input_event ev;
        int rd = read( d->m_fd, &ev, sizeof( struct input_event ) );
        if( rd >= ( int ) sizeof( struct input_event ) )
        {
            QEvent::Type eventType = QEvent::Type( QEvent::User + ev.type );

            switch( eventType )
            {
                case GluonInput::Button:
                    emit buttonStateChanged( mapKeyCode( ev.code ), ev.value );
                    break;
                case GluonInput::RelativeAxis:
                    emit relAxisMoved( ev.code, ev.value );
                    break;
                case GluonInput::AbsoluteAxis:
                    emit absAxisMoved( ev.code, ev.value );
                    break;
                default:
                    break;
            }
        }
    }
}

bool InputThread::openDevice( const QString& devicePath )
{
    if(( d->m_fd = open( devicePath.toUtf8(), O_RDONLY ) ) == -1 )
    {
        qDebug() << "Could not open the device: " << devicePath;
        d->m_error = true;
        d->m_msgError += "Could not open the device\n";
        return false;
    }

    return true;
}

// int InputThread::readSystemFS()
// {

/* From here, we can call get_sysattr_value() for each file
   in the device's /sys entry. The strings passed into these
   functions (idProduct, idVendor, serial, etc.) correspond
   directly to the files in the directory which represents
   the USB device. Note that USB strings are Unicode, UCS2
   encoded, but the strings returned from
   udev_device_get_sysattr_value() are UTF-8 encoded. */
// d->m_deviceName = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "name"));

// quint64 bit[EV_MAX][NBITS(KEY_MAX)];
// int abs[5];
// memset(bit, 0, sizeof(bit));

// bool ok;
// int k;
// bit[0][0] = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/ev")).toULong(&ok, 16);

// for (int i = 1; i < EV_MAX; ++i) {
// if (test_bit(i, bit[0])) {
// if (!i)
// continue;
// switch (i) {
// case EV_KEY:
// {
// k = 0;
// QStringList keySections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/key")).split(" ");
// for (QStringList::iterator istr = keySections.end(); istr != keySections.begin(); ++k)
// bit[i][k] = (--istr)->toULongLong(&ok, 16);

// for (int j = 0; j < KEY_MAX; ++j) {
// if (test_bit(j, bit[i]))
// d->m_buttonCapabilities.append(j);
// }
// }
// break;
// case EV_REL:
// {
// k = 0;
// QStringList relSections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/rel")).split(" ");
// for (QStringList::iterator istr = relSections.end(); istr != relSections.begin(); ++k)
// bit[i][k] = (--istr)->toULongLong(&ok, 16);

// for (int j = 0; j < KEY_MAX; ++j) {
// if (test_bit(j, bit[i]))
// d->m_relAxisCapabilities.append(j);
// }
// }
// break;
// case EV_ABS:
// {
// for (int j = 0; j < ABS_MAX; ++j) {
// if (test_bit(j, bit[i])) {
// k = 0;
// QStringList absSections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/abs")).split(" ");
// for (QStringList::iterator istr = absSections.end(); istr != absSections.begin(); ++k)
// abs[k++] = (--istr)->toULongLong(&ok, 16);

// AbsVal cabs(0, 0, 0, 0);
// for (int k = 0; k < 5; ++k) {
// if ((k < 3) || abs[k]) {
// switch (k) {
// case 0:
// cabs.value = abs[k];
// break;
// case 1:
// cabs.min = abs[k];
// break;
// case 2:
// cabs.max = abs[k];
// break;
// case 3:
// cabs.fuzz = abs[k];
// break;
// case 4:
// cabs.flat = abs[k];
// break;
// }
// }
// }
// d->m_absAxisCapabilities.append(j);
// d->m_absAxisInfos.append(cabs);
// }
// }
// }
// break;
// default:
// break;
// }
// }
// }

// //===============Find Force feedback ?? ===============

// d->m_deviceType = GluonInput::UnknownDevice;

// if (d->m_buttonCapabilities.contains(BTN_TOUCH)) {
// d->m_deviceType  = GluonInput::TouchDevice;
// }

// if (d->m_buttonCapabilities.contains(BTN_STYLUS)
// || d->m_buttonCapabilities.contains(ABS_PRESSURE)) {
// d->m_deviceType  = GluonInput::MouseDevice;
// }

// if (d->m_buttonCapabilities.contains(BTN_TRIGGER)) {
// d->m_deviceType  = GluonInput::JoystickDevice;
// }

// if (d->m_buttonCapabilities.contains(BTN_MOUSE)) {
// d->m_deviceType  = GluonInput::MouseDevice;
// }

// if (d->m_buttonCapabilities.contains(KEY_ENTER))    {
// d->m_deviceType  = GluonInput::KeyboardDevice;
// }

// return 0;
// }

void InputThread::readInformation()
{
    if( d->m_fd == -1 )
    {
        qDebug() << "The device is not open";
        d->m_error = true;
        d->m_msgError = "The device is not open\n";
        return;
    }

    // Get the device ID
    if( ioctl( d->m_fd, EVIOCGID, &d->m_device_info ) )
    {
        qDebug() << "Could not retrieve the information of the device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve the information of the device\n";
        d->m_error = true;
        return;
    }

    char devname[256] = "Unknown";
    // Get the device name
    if( ioctl( d->m_fd, EVIOCGNAME( sizeof( devname ) ), devname ) == -1 )
    {
        qDebug() << "Could not retrieve the name of the device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve the name of the device\n";
        d->m_error = true;
        return;
    }
    d->m_deviceName = QString( devname );

    ///this next bit can be shared across platform
    unsigned long bit[EV_MAX][NBITS( KEY_MAX )];
    int abs[5];
    memset( bit, 0, sizeof( bit ) );
    // Get the feature types here
    ioctl( d->m_fd, EVIOCGBIT( 0, EV_MAX ), bit[0] );

    d->m_buttonCapabilities.clear();
    d->m_absAxisInfos.clear();

    for( int i = 0; i < EV_MAX; ++i )
    {
        if( test_bit( i, bit[0] ) )
        {
            if( !i )
            {
                continue;
            }

            // Get the features of the desired feature type here
            ioctl( d->m_fd, EVIOCGBIT( i, KEY_MAX ), bit[i] );
            switch( i )
            {
                case EV_KEY:
                {
                    for( int j = 0; j < KEY_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                            d->m_buttonCapabilities.append( j );
                    }
                }
                break;
                case EV_REL:
                {
                    for( int j = 0; j < KEY_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                            d->m_relAxisCapabilities.append( j );
                    }
                }
                break;
                case EV_ABS:
                {
                    for( int j = 0; j < ABS_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                        {
                            // Get abs value/limits
                            ioctl( d->m_fd, EVIOCGABS( j ), abs );
                            AbsVal cabs( 0, 0, 0, 0 );
                            for( int k = 0; k < 5; ++k )
                            {
                                if(( k < 3 ) || abs[k] )
                                {
                                    switch( k )
                                    {
                                        case 0:
                                            cabs.value = abs[k];
                                            break;
                                        case 1:
                                            cabs.min = abs[k];
                                            break;
                                        case 2:
                                            cabs.max = abs[k];
                                            break;
                                        case 3:
                                            cabs.fuzz = abs[k];
                                            break;
                                        case 4:
                                            cabs.flat = abs[k];
                                            break;
                                    }
                                }
                            }
                            d->m_absAxisCapabilities.append( j );
                            d->m_absAxisInfos.append( cabs );
                        }
                    }
                }
                break;
                default:
                    break;
            }
        }
    }

    //===============Find Force feedback ?? ===============

    d->m_deviceType = GluonInput::UnknownDevice;

    if( d->m_buttonCapabilities.contains( BTN_TOUCH ) )
    {
        d->m_deviceType  = GluonInput::TouchDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_STYLUS )
            || d->m_buttonCapabilities.contains( ABS_PRESSURE ) )
    {
        d->m_deviceType  = GluonInput::MouseDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_TRIGGER ) )
    {
        d->m_deviceType  = GluonInput::JoystickDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_MOUSE ) )
    {
        d->m_deviceType  = GluonInput::MouseDevice;
    }

    if( d->m_buttonCapabilities.contains( KEY_ENTER ) )
    {
        d->m_deviceType  = GluonInput::KeyboardDevice;
    }
}

int InputThread::joystickXAxis()
{
    return ABS_X;
}

int InputThread::joystickYAxis()
{
    return ABS_Y;
}

int InputThread::joystickZAxis()
{
    return ABS_Z;
}

void InputThread::stop()
{
    quit();
}

struct input_id InputThread::device_info() const
{
    return d->m_device_info;
}

int InputThread::vendor() const
{
    return d->m_device_info.vendor;
}

int InputThread::product() const
{
    return d->m_device_info.product;
}

int InputThread::version() const
{
    return d->m_device_info.version;
}

int InputThread::bustype()const
{
    return d->m_device_info.bustype;
}

QList<int> InputThread::buttonCapabilities() const
{
    return d->m_buttonCapabilities;
}

QList<int> InputThread::absAxisCapabilities() const
{
    return d->m_absAxisCapabilities;
}

QList<int> InputThread::relAxisCapabilities() const
{
    return d->m_relAxisCapabilities;
}

AbsVal InputThread::axisInfo( int axisCode ) const
{
    return d->m_absAxisInfos[axisCode];
}

const QString InputThread::deviceName() const
{
    return d->m_deviceName;
}

GluonInput::DeviceFlag InputThread::deviceType() const
{
    return d->m_deviceType;
}

bool InputThread::isEnabled() const
{
    return isRunning();
}

bool InputThread::error()
{
    return d->m_error;
}

QString InputThread::msgError()
{
    return d->m_msgError;
}

void InputThread::closeDevice()
{
    if( close( d->m_fd ) )
        qDebug() << "Could not close the device: " << d->m_devicePath << endl;
}

#include "inputthread.moc"
