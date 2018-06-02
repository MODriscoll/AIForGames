#include "InputLibrary.h"

#include "Application.h"
#include "Input.h"

// TO DO LIST:

// Make a controller component
// to handle callbacks instead
// of this, have a remove
// bindings option for the
// controller component to use

// Construct this input library
InputLibrary::InputLibrary()
{
	// Assert that both input IDs and input Status have a int base
	static_assert(std::is_same<Input_Key_ID_Type, int>::value,
				  "Input_Key_ID enum class must have an underlying type of int");

	static_assert(std::is_same<Input_Button_ID_Type, int>::value,
				  "Input_Button_ID enum class must have an underlying type of int");

	static_assert(std::is_same<Input_Status_Type, int>::value,
				  "Input_Status enum class must have an underlying type of int");

	// Create the key press callback lambda
	aie::Input::getInstance()->attachKeyObserver([this](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Was this key just pressed ( 1 )
		if (action == 1)
		{
			// Set that this key has just been pressed
			OnKeyPress(static_cast<Input_Key_ID>(key));
		}

		// Was this key just released ( 0 )
		if (action == 0)
		{
			// Set that this key has just been released
			OnKeyRelease(static_cast<Input_Key_ID>(key));
		}
	});

	// Create the button press callback lambda
	aie::Input::getInstance()->attachMouseButtonObserver([this](GLFWwindow* window, int button, int action, int mods)
	{
		// Was this button just pressed ( 1 )
		if (action == 1)
		{
			// Set that this button has just been pressed
			OnButtonPress(static_cast<Input_Button_ID>(button));
		}

		// Was this button just released ( 0 )
		if (action == 0)
		{
			// Set that this button has just been released
			OnButtonRelease(static_cast<Input_Button_ID>(button));
		}
	});

	// Create the mouse move callback lambda
	aie::Input::getInstance()->attachMouseMoveObserver([this](GLFWwindow* window, double x, double y)
	{
		// Set the new position of the mouse
		OnMouseMove(x, y);
	});

	// Create the mouse scroll callback lambda
	aie::Input::getInstance()->attachMouseScrollObserver([this](GLFWwindow* window, double xoffset, double yoffset)
	{
		// Set the new scroll of the mouse
		OnMouseScroll(xoffset, yoffset);
	});
}

// Destroy this input library
InputLibrary::~InputLibrary()
{

}

// Update the key to just being pressed
void InputLibrary::OnKeyPress(Input_Key_ID a_ID)
{
	// Set this key to being pressed
	m_Keys[a_ID].m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Press);

	// Set this key to needing to be updated
	m_UpdateKeys.push_back(a_ID);
}

// Update the key to just being released
void InputLibrary::OnKeyRelease(Input_Key_ID a_ID)
{
	// Set this key to being released
	m_Keys[a_ID].m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Release);

	// Set this key to needing to be updated
	m_UpdateKeys.push_back(a_ID);
}

// Update the button to just being pressed
void InputLibrary::OnButtonPress(Input_Button_ID a_ID)
{
	// Set this button to being pressed
	m_Buttons[a_ID].m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Press);

	// Set this button to needing to be updated
	m_UpdateButtons.push_back(a_ID);
}

// Update the button to just being released
void InputLibrary::OnButtonRelease(Input_Button_ID a_ID)
{
	// Set this button to being released
	m_Buttons[a_ID].m_Status = static_cast<Input_Status_Type>(Input_Status::Input_Release);

	// Set this button to needing to be updated
	m_UpdateButtons.push_back(a_ID);
}

// Update the mouses position
void InputLibrary::OnMouseMove(double a_PositionX, double a_PositionY)
{
	// Set the new position of the mouse
	m_MousePosX = a_PositionX;
	m_MousePosY = a_PositionY;

	// Set the mouse to having moved
	m_MouseMove = true;
}

// Update the mouses scroll
void InputLibrary::OnMouseScroll(double a_XOffset, double a_YOffset)
{
	// Set the new scroll of the mouse
	m_MouseScroll += a_YOffset;
}

// Bind a new key for the library to manage
void InputLibrary::BindKey(Input_Key_ID a_ID, Input_Status a_OnStatus, std::function<void()> a_Callback)
{
	// Add this callback depending on what type it is
	if (a_OnStatus == Input_Status::Input_Press)
	{
		// Add this callback to the press callbacks of the requested key
		m_Keys[a_ID].m_KeyPressCallbacks.push_back(a_Callback);
	}
	else if (a_OnStatus == Input_Status::Input_Release)
	{ 
		// Add this callback to the release callbacks of the requested key
		m_Keys[a_ID].m_KeyReleaseCallbacks.push_back(a_Callback);
	}
}

// Bind a new axis for the library to manage
void InputLibrary::BindKeyToAxis(std::string a_Name, Input_Key_ID a_ID, float a_Value)
{
	// Add this key to the requested axis
	m_Axes[a_Name].m_Values.push_back(std::make_pair(a_ID, a_Value));
}

// Bind a new button for the library to manage
void InputLibrary::BindButton(Input_Button_ID a_ID, Input_Status a_OnStatus, std::function<void()> a_Callback)
{
	// Add this callback depending on what type it is
	if (a_OnStatus == Input_Status::Input_Press)
	{
		// Add this callback to the press callbacks of the requested button
		m_Buttons[a_ID].m_ButtonPressCallbacks.push_back(a_Callback);
	}
	else if (a_OnStatus == Input_Status::Input_Release)
	{
		// Add this callback to the release callbacks of the requested button
		m_Buttons[a_ID].m_ButtonReleaseCallbacks.push_back(a_Callback);
	}
}

// Add a new callback for an axis to execute
void InputLibrary::BindAxis(std::string a_Name, std::function<void(float)> a_Callback)
{
	// Add this callback to the requested axis
	m_Axes[a_Name].m_Callbacks.push_back(a_Callback);
}

// Remove an axis
void InputLibrary::RemoveAxis(std::string a_Name)
{
	auto it = m_Axes.find(a_Name);

	if (it != m_Axes.end())
	{
		m_Axes.erase(it);
	}
}

// Return if this key was pressed this frame
bool InputLibrary::WasKeyPressed(Input_Key_ID a_ID)
{
	// Only compare this keys status to the press input status
	return (m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press));
}

// Return if this key was released this frame
bool InputLibrary::WasKeyReleased(Input_Key_ID a_ID)
{
	// Only compare this keys status to the release input status
	return (m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Release));
}

// Return if this key is currently down
bool InputLibrary::IsKeyDown(Input_Key_ID a_ID)
{
	// Compare this keys status to press and down input status
	return (m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press) ||
		    m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Hold));
}

// Return if this key is currently up
bool InputLibrary::IsKeyUp(Input_Key_ID a_ID)
{
	// Compare this keys status to release and up input status
	return (m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Release) ||
		    m_Keys[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Free));
}

// Return if this button was pressed this frame
bool InputLibrary::WasButtonPressed(Input_Button_ID a_ID)
{
	// Only compare this buttons status to the press input status
	return (m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press));
}

// Return if this button was released this frame
bool InputLibrary::WasButtonReleased(Input_Button_ID a_ID)
{
	// Only compare this buttons status to the release input status
	return (m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Release));
}

// Return if this button is currently down
bool InputLibrary::IsButtonDown(Input_Button_ID a_ID)
{
	// Compare this buttons status to press and down input status
	return (m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press) ||
			m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Hold));
}

// Return if this button is currently up
bool InputLibrary::IsButtonUp(Input_Button_ID a_ID)
{
	// Compare this buttons status to release and up input status
	return (m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Release) ||
			m_Buttons[a_ID].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Free));
}

// Return only the X position of the mouse
int InputLibrary::GetMouseX() const
{
	return (int)m_MousePosX;
}

// Return only the Y position of the mouse
int InputLibrary::GetMouseY() const
{
	return (int)m_MousePosY;
}

// Return the mouses position
void InputLibrary::GetMousePos(int& a_OutX, int& a_OutY)
{
	// Set the given variables to the mouses position
	a_OutX = (int)m_MousePosX;
	a_OutY = (int)m_MousePosY;
}

// Return if the mouse was moved
bool InputLibrary::WasMouseMoved()
{
	return m_MouseMove;
}

// Return the scroll of the mouse
double InputLibrary::GetMouseScroll()
{
	return m_MouseScroll;
}

// Update the library
void InputLibrary::UpdateLibrary()
{
	// Get the delta time of this frame
	float deltaTime = aie::Application::GetTimer()->GetDeltaTime() * 2;

	// Update the status of all the keys pressed this frame
	for (auto& Key : m_UpdateKeys)
	{
		// Cycle through all of callbacks for this key ( depending on its status )
		for (auto& Callback : m_Keys[Key].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press) ? 
			m_Keys[Key].m_KeyPressCallbacks : m_Keys[Key].m_KeyReleaseCallbacks)
		{
			// Execute this callback
			Callback();
		}

		// Add two to the current status of this key
		m_Keys[Key].m_Status += 2;
	}

	// Update the status of all the buttons pressed this frame
	for (auto& Button : m_UpdateButtons)
	{
		// Cycle through all of callbacks for this button ( depending on its status )
		for (auto& Callback : m_Buttons[Button].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Press) ?
			m_Buttons[Button].m_ButtonPressCallbacks : m_Buttons[Button].m_ButtonReleaseCallbacks)
		{
			// Execute this callback
			Callback();
		}

		// Add two to the current status of this button
		m_Buttons[Button].m_Status += 2;
	}

	// Create a flag for the next update loop to utilise
	bool axisUpdated;

	// Cycle through all axes
	for (auto& Axis : m_Axes)
	{
		// Set that the axis hasn't been updated
		axisUpdated = false;

		// Cycle through all of the bindings in this axis
		for (auto& Binding : Axis.second.m_Values)
		{
			// Is this binding currently being held down
			if (m_Keys[Binding.first].m_Status == static_cast<Input_Status_Type>(Input_Status::Input_Hold))
			{
				// Either increase or decrease the current value depending on the value
				Axis.second.m_curValue += (Binding.second > 0 ? deltaTime : -deltaTime);

				// Make sure the current value doesn't go beyond the set value
				Axis.second.m_curValue = (fabs(Axis.second.m_curValue) > fabs(Binding.second)) ? // If (cond) then [ 1 ]
					// Due to the first check, make sure the the signbits are the
					// same to prevent current value from instantly jumping to value
					(std::signbit(Binding.second) == std::signbit(Axis.second.m_curValue) ?	// If (cond) then [ 2 ]
						// Set current value to the value
						Binding.second 
							: // Else [ 2 ]
						// Don't change the current value
						Axis.second.m_curValue) 
					: // Else [ 1 ]
						// Don't change the current value
						Axis.second.m_curValue;

				// Set that this axis has been updated
				axisUpdated = true;

				// Don't check anymore bindings
				break;
			}
		}

		// Was the axis not updated? ( we don't decrease current value if its zero )
		if (!axisUpdated && Axis.second.m_curValue != 0)
		{
			// Is the current value currently negative?
			if (std::signbit(Axis.second.m_curValue))
			{
				// Add to the current value
				Axis.second.m_curValue += deltaTime;

				// Make sure current value doesn't go beyond 0
				Axis.second.m_curValue = Axis.second.m_curValue > 0 ? 0 : Axis.second.m_curValue;
			}
			else
			{
				// Take from the current value
				Axis.second.m_curValue -= deltaTime;

				// Make sure current value doesn't go beyond 0
				Axis.second.m_curValue = Axis.second.m_curValue < 0 ? 0 : Axis.second.m_curValue;
			}
		}

		// Cycle through this axis callbacks
		for (auto& Callback : Axis.second.m_Callbacks)
		{
			// Execute this callback
			Callback(Axis.second.m_curValue);
		}		
	}

	// Clear the keys and buttons that need to be updated
	m_UpdateKeys.clear();
	m_UpdateButtons.clear();

	// Set the mouse to no longer having moved
	m_MouseMove = false;

	// temp
	m_MouseScroll = 0.0;
}
