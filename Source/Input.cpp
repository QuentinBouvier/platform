#include "../Headers/Input.h"

//------------------------------------------------------//
//														//
//			Class constructors and destructor.			//
//														//
//------------------------------------------------------//

Input::Input() :
m_x(0),
m_y(0),
m_rx(0),
m_ry(0),
m_mouseWheel(0),
m_windowClosed(false)
{
	for (int i(0); i < SDL_NUM_SCANCODES; i++)
	{
		m_keys[i] = false;
	}
	for (int i(0); i < 8; i++)
	{
		m_mouseButtons[i] = false;
	}
}

Input::~Input()
{}

//------------------------------------------------------//
//														//
//					Public Methods						//
//														//
//------------------------------------------------------//

void Input::updateEvents()
{
	//Reinitialize mouse relative position and wheel state to be
	//sure it does not send false positive
	m_rx = 0;
	m_ry = 0;
	m_mouseWheel = 0;

	while (SDL_PollEvent(&m_events))
	{

		switch (m_events.type)
		{
			case SDL_KEYDOWN:
				m_keys[m_events.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				m_keys[m_events.key.keysym.scancode] = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_mouseButtons[m_events.button.button] = true;
				break;

			case SDL_MOUSEBUTTONUP:
				m_mouseButtons[m_events.button.button] = false;
				break;

			case SDL_MOUSEMOTION:
				m_x = m_events.motion.x;
				m_y = m_events.motion.y;

				m_rx = m_events.motion.xrel;
				m_ry = m_events.motion.yrel;
				break;

			case SDL_MOUSEWHEEL:
				if (m_events.wheel.y < 0)
					m_mouseWheel = -1;
				else
					m_mouseWheel = 1;
				break;

			case SDL_WINDOWEVENT:
				if (m_events.window.event == SDL_WINDOWEVENT_CLOSE)
					m_windowClosed = true;
				break;

			default:
				break;
		}
	}
}

bool Input::getKey(const SDL_Scancode key) const
{
	return m_keys[key];
}

bool Input::getMouseButton(const Uint8 button) const
{
	return m_mouseButtons[button];
}

bool Input::isMouseMoved() const
{
	if (m_rx == 0 && m_ry == 0)
		return false;
	else
		return true;
}

//------------------------------------------------------//
//														//
//					Setters / Getters					//
//														//
//------------------------------------------------------//

bool Input::getWindowClosingEvent() const
{
	return m_windowClosed;
}

int Input::getX() const
{
	return m_x;
}

int Input::getY() const
{
	return m_y;
}

int Input::getRX() const
{
	return m_rx;
}

int Input::getRY() const
{
	return m_ry;
}

int Input::getMouseWheel() const
{
	return m_mouseWheel;
}


//------------------------------------------------------//
//														//
//					  Static Methods					//
//														//
//------------------------------------------------------//

void Input::displayMouseButton(bool toggle)
{
	if (toggle)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

void Input::captureCursor(bool toggle)
{
	if (toggle)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

