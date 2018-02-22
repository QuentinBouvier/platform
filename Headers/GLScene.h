#ifndef GLSCENE_H
#define GLSCENE_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <GL/glew.h>

#include "Global.h"
#include "Window.h"
#include "Input.h"

class GLScene
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructor and destructor.			//
	//														//
	//------------------------------------------------------//
	GLScene();
	GLScene(Size size);
	virtual ~GLScene();

	//------------------------------------------------------//
	//														//
	//					Public Methods						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Main loop virtual function for every display in		//
	//	members class										//
	//------------------------------------------------------//
	virtual void mainLoop() = 0;

	//------------------------------------------------------//
	//														//
	//					Setters / Getters					//
	//														//
	//------------------------------------------------------//

protected:

	Size m_sceneSize;

	SDL_Event m_event;
	Input m_inputs;

};

#endif /* GLSCENE_H */