#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>

#include <SDL.h>

class Input
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//
	Input();
	~Input();

	//------------------------------------------------------//
	//														//
	//					Public Methods						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Poll possible event needed by the player to			//
	//	interact with the game and put the result into the	//
	//	right member of the class.							//
	//------------------------------------------------------//
	void updateEvents();

	//------------------------------------------------------//
	//	returns the state of the polled key					//
	//------------------------------------------------------//
	bool getKey(const SDL_Scancode key) const;

	//------------------------------------------------------//
	//	returns the state of the polled mouse button		//
	//------------------------------------------------------//
	bool getMouseButton(const Uint8 button) const;

	//------------------------------------------------------//
	//	returns true is the mouse has been moved			//
	//------------------------------------------------------//
	bool isMouseMoved() const;

	//------------------------------------------------------//
	//														//
	//					Setters / Getters					//
	//														//
	//------------------------------------------------------//

	bool getWindowClosingEvent() const;

	int getX() const;
	int getY() const;
	int getRX() const;
	int getRY() const;

	//------------------------------------------------------//
	//	Returns 1 if the mousewheel is rolled up and -1 if	//
	//	it's rolled down.									//
	//------------------------------------------------------//
	int getMouseWheel() const;


	//------------------------------------------------------//
	//														//
	//					  Static Methods					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//Toggles the mouse cursor display						//
	//------------------------------------------------------//
	static void displayMouseButton(bool toggle);

	//------------------------------------------------------//
	//Toggles the cursor capture state						//
	//------------------------------------------------------//
	static void captureCursor(bool toggle);
	
private:

	bool m_keys[SDL_NUM_SCANCODES];
	bool m_mouseButtons[8];

	SDL_Event m_events;
	int m_mouseWheel;
	int m_x;
	int m_y;
	int m_rx;
	int m_ry;

	bool m_windowClosed;

};

#endif /* INPUTS_H */