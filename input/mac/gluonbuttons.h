#ifndef GLUONBUTTONS_H
#define GLUONBUTTONS_H

#include <QtCore/QObject>

#include "gluon_input_export.h"
#include "core/singleton.h"
#include "gluondevices.h"

namespace GluonInput 
{
	class GLUON_INPUT_EXPORT GluonButtons :public GluonCore::Singleton<GluonButtons>
    {
		Q_OBJECT
		Q_ENUMS(KeyboardButton)
		Q_ENUMS(JoystickButton)
		Q_ENUMS(MouseButton)
		Q_ENUMS(RelAbs)
		
		public:
			
			
		//#warning remove this and do not use the QEvent thing
			/*enum InputTypeFlag 
			{
				Key = QEvent::Type(QEvent::User+1),
				RelativeAxis = QEvent::Type(QEvent::User+2),
				AbsoluAxis = QEvent::Type(QEvent::User+3)
			};
			
			Q_ENUMS(InputTypeFlag)*/
			
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
				RIGT_BRACKET,
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
				Keypad_PLUS_AND_MINUS,
				Keypad_Clear,
				Keypad_Clear_Entry,
				Keypad_Binary,
				Keypad_Octal,
				Keypad_Decimal,
				Keypad_Hexadecimal,
				LeftControl = 224,
				LeftShift,
				LeftAlt,
				Left_GUI,
				RightControl,
				RightShift,
				RightAlt,
				Right_GUI
			};
			
			enum RelAbs
			{
				Misc = 0,
				X_AXIS = 48,
				Y_AXIS,
				Z_AXIS,
				ROTATION_X_AXIS,
				ROTATION_Y_AXIS,
				ROTATION_Z_AXIS,
				Dial = 55,
				Wheel,
				Hat_Switch,
				XTilt = 61,
				YTilt,
				Rudder = 186,
				Throttle,
				Gas = 196,
				Brake
			};	 
			
			//atm only support for 15 mouse buttons :p
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
				MOUSE_BUTTON_NINE,
				MOUSE_BUTTON_TEN,
				MOUSE_BUTTON_ELEVEN,
				MOUSE_BUTTON_TWELVE,
				MOUSE_BUTTON_THIRTEEN,
				MOUSE_BUTTON_FOURTEEN,
				MOUSE_BUTTON_FIFTEEN
			};
			
			//atm only support for 15 joystick buttons :p
			enum JoystickButton
			{
				JOYSTICK_BUTTON_ONE = 1,
				JOYSTICK_BUTTON_TWO,
				JOYSTICK_BUTTON_THREE,
				JOYSTICK_BUTTON_FOUR,
				JOYSTICK_BUTTON_FIVE,
				JOYSTICK_BUTTON_SIX,
				JOYSTICK_BUTTON_SEVEN,
				JOYSTICK_BUTTON_EIGHT,
				JOYSTICK_BUTTON_NINE,
				JOYSTICK_BUTTON_TEN,
				JOYSTICK_BUTTON_ELEVEN,
				JOYSTICK_BUTTON_TWELVE,
				JOYSTICK_BUTTON_THIRTEEN,
				JOYSTICK_BUTTON_FOURTEEN,
				JOYSTICK_BUTTON_FIFTEEN
			};
		
			GluonButtons();
	
			QString buttonName(DeviceFlag deviceType , int code);
			QString axisName(DeviceFlag deviceType, int code);
		
		private:
			~GluonButtons();
		
    };
}

//@}
#endif // KCL_H
