#pragma once

#include <functional>	// For callbacks
#include <map>			// For storing bindings
#include <string>		// For identifying axes bindings
#include <vector>		// For storing callbacks and updates

// Enum of ID codes for keys
enum class Input_Key_ID : int
{
	// Unknow key
	Unknown = -1,

	// Key IDs
	Key_Space = 32,
	Key_Apostrophe = 39,
	Key_Comma = 44,
	Key_Minus = 45,
	Key_Period = 46,
	Key_Slash = 47,
	Key_0 = 48,
	Key_1 = 49,
	Key_2 = 50,
	Key_3 = 51,
	Key_4 = 52,
	Key_5 = 53,
	Key_6 = 54,
	Key_7 = 55,
	Key_8 = 56,
	Key_9 = 57,
	Key_SemiColon = 59,
	Key_Equal = 61,
	Key_A = 65,
	Key_B = 66,
	Key_C = 67,
	Key_D = 68,
	Key_E = 69,
	Key_F = 70,
	Key_G = 71,
	Key_H = 72,
	Key_I = 73,
	Key_J = 74,
	Key_K = 75,
	Key_L = 76,
	Key_M = 77,
	Key_N = 78,
	Key_O = 79,
	Key_P = 80,
	Key_Q = 81,
	Key_R = 82,
	Key_S = 83,
	Key_T = 84,
	Key_U = 85,
	Key_V = 86,
	Key_W = 87,
	Key_X = 88,
	Key_Y = 89,
	Key_Z = 90,
	Key_LeftBracket = 91,
	Key_BackSlash = 92,
	Key_RightBracket = 93,
	Key_GraveAccent = 96,
	Key_Escape = 256,
	Key_Enter = 257,
	Key_Tab = 258,
	Key_Backspace = 259,
	Key_Insert = 260,
	Key_Delete = 261,
	Key_Right = 262,
	Key_Left = 263,
	Key_Down = 264,
	Key_Up = 265,
	Key_PageUp = 266,
	Key_PageDown = 267,
	Key_Home = 268,
	Key_End = 269,
	Key_CapsLock = 280,
	Key_ScrollLock = 281,
	Key_NumLock = 282,
	Key_PrintScreen = 283,
	Key_Pause = 284,
	Key_F1 = 290,
	Key_F2 = 291,
	Key_F3 = 292,
	Key_F4 = 293,
	Key_F5 = 294,
	Key_F6 = 295,
	Key_F7 = 296,
	Key_F8 = 297,
	Key_F9 = 298,
	Key_F10 = 299,
	Key_F11 = 300,
	Key_F12 = 301,
	Key_F13 = 302,
	Key_F14 = 303,
	Key_F15 = 304,
	Key_F16 = 305,
	Key_F17 = 306,
	Key_F18 = 307,
	Key_F19 = 308,
	Key_F20 = 309,
	Key_F21 = 310,
	Key_F22 = 311,
	Key_F23 = 312,
	Key_F24 = 313,
	Key_F25 = 314,
	Key_Kp_0 = 320,
	Key_Kp_1 = 321,
	Key_Kp_2 = 322,
	Key_Kp_3 = 323,
	Key_Kp_4 = 324,
	Key_Kp_5 = 325,
	Key_Kp_6 = 326,
	Key_Kp_7 = 327,
	Key_Kp_8 = 328,
	Key_Kp_9 = 329,
	Key_Kp_Decimal = 330,
	Key_Kp_Divide = 331,
	Key_Kp_Multiply = 332,
	Key_Kp_Subtract = 333,
	Key_Kp_Add = 334,
	Key_Kp_Enter = 335,
	Key_Kp_Equal = 336,
	Key_LeftShift = 340,
	Key_LeftControl = 341,
	Key_LeftAlt = 342,
	Key_RightShift = 344,
	Key_RightControl = 345,
	Key_RightAlt = 346
};

// The base type of the input key IDs enum class ( Should be int )
using Input_Key_ID_Type = std::underlying_type<Input_Key_ID>::type;

// Enum of ID codes for buttons
enum class Input_Button_ID : int
{
	// Unknow key
	Unknown = -1,

	// Mouse IDs
	Mouse_Left = 0,
	Mouse_Right = 1,
	Mouse_Middle = 2,
	Mouse_4 = 3,
	Mouse_5 = 4,
	Mouse_6 = 5,
	Mouse_7 = 6,
	Mouse_8 = 7
};

// The base type of the input button IDs enum class ( Should be int )
using Input_Button_ID_Type = std::underlying_type<Input_Button_ID>::type;

// Input types ( to be used to signal callbacks )
enum class Input_Status : int
{
	// For buttons to use
	Input_Press = 0,
	Input_Release = 1,

	// For axes to use
	Input_Hold = 2,
	Input_Free = 3
};

// The base type of the input status enum class ( Should be int )
using Input_Status_Type = std::underlying_type<Input_Status>::type;

class InputLibrary
{
private:

	// Key binding struct ( controls keys )
	struct KeyBinding
	{
		// Call back functions for this key
		std::vector<std::function<void()>> m_KeyPressCallbacks;
		std::vector<std::function<void()>> m_KeyReleaseCallbacks;

		// This keys status, should have input action status
		Input_Status_Type m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Free);
	};

	// Axis binding struct ( use key bindings to get value )
	struct AxisBinding
	{
		// Callback functions for this axis
		std::vector<std::function<void(float)>> m_Callbacks;

		// This axes binder current value
		float m_curValue = 0;

		// Key bindings and values associated with those keys
		std::vector<std::pair<Input_Key_ID, float>> m_Values;
	};

	// Button binding struct ( controls mouse buttons )
	struct ButtonBinding
	{
		// Call back functions for this button
		std::vector<std::function<void()>> m_ButtonPressCallbacks;
		std::vector<std::function<void()>> m_ButtonReleaseCallbacks;

		// This buttons status, should have input action status
		Input_Status_Type m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Free);
	};

public:

	// Bind a new callback based on the given key
	void BindKey(Input_Key_ID a_ID, Input_Status a_OnStatus, std::function<void()> a_Callback);

	// Bind a new axis based on the given name, key and value
	void BindKeyToAxis(std::string a_Name, Input_Key_ID a_ID, float a_Value);

	// Bind a new callback based on the given button
	void BindButton(Input_Button_ID a_ID, Input_Status a_OnStatus, std::function<void()> a_Callback);

	// Attach a callback to an axis
	void BindAxis(std::string a_Name, std::function<void(float)> a_Callback);

	// Temp function for now
	void RemoveAxis(std::string a_Name);

	// Confirm a keys status
	bool WasKeyPressed(Input_Key_ID a_ID);
	bool WasKeyReleased(Input_Key_ID a_ID);
	bool IsKeyDown(Input_Key_ID a_ID);
	bool IsKeyUp(Input_Key_ID a_ID);

	// Confirm a buttons status
	bool WasButtonPressed(Input_Button_ID a_ID);
	bool WasButtonReleased(Input_Button_ID a_ID);
	bool IsButtonDown(Input_Button_ID a_ID);
	bool IsButtonUp(Input_Button_ID a_ID);

	// Get the mouse position ( either axis or both )
	int GetMouseX() const;
	int GetMouseY() const;
	void GetMousePos(int& a_OutX, int& a_OutY);

	// Get if the mouse was moved
	bool WasMouseMoved();

	// Get the scroll of the mouse
	double GetMouseScroll();

	static InputLibrary* Instance()
	{
		// Create a static input library for the singleton
		static InputLibrary m_Library;

		// Return the static library
		return &m_Library;
	}

	// Update the library
	void UpdateLibrary();

private:

	// Private constructor and deconstructor
	InputLibrary();
	~InputLibrary();

	// For the observer to call when keys are pressed
	void OnKeyPress(Input_Key_ID a_ID);
	void OnKeyRelease(Input_Key_ID a_ID);

	// For the observer to call when buttons are pressed
	void OnButtonPress(Input_Button_ID a_ID);
	void OnButtonRelease(Input_Button_ID a_ID);

	// For the observer to call when the mouse moves
	void OnMouseMove(double a_PositionX, double a_PositionY);

	// For the observer to call when the mouse is scrolled
	void OnMouseScroll(double a_XOffset, double a_YOffset);

	// Maps of all the bindings
	std::map<Input_Key_ID, KeyBinding> m_Keys;
	std::map<std::string, AxisBinding> m_Axes;
	std::map<Input_Button_ID, ButtonBinding> m_Buttons;
	
	// Vectors of all the inputs pressed in one frame
	std::vector<Input_Key_ID> m_UpdateKeys;
	std::vector<Input_Button_ID> m_UpdateButtons;

	// The mouse position relative to the window
	double m_MousePosX, m_MousePosY;
	// If the mouse was recently moved
	bool m_MouseMove;

	// The current scroll of the mouse
	double m_MouseScroll;

	// NOTE:
	// Make a map that stores keys pressed each frame ( cleared at end of frame )
	// Map will be std::map<Input_Key_ID, bool>
	// Key_ID represents the key which can be used to index the key
	// bool represents if the key was pressed or not

	// if the key was pressed, it means it will have been set by this library and set to true
	// if the key wasn't pressed, it means a new map node will be created and the bool will default to false

	// Make a function that returns a const reference so indexing can be used like

	// auto& ref = input->GetPressedKeys();

	// if (ref[Key_ID])
	//	    { /..../ }
};