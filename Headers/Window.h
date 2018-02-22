#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <memory>

#include <SDL.h>

#include <GL/glew.h>

#include "Global.h"

class Window
{
public:

	//------------------------------------------------------//
	//														//
	//					  Static Methods					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Initialize the whole context for the program, using	//
	//	SDL2 and OpenGL										//
	//------------------------------------------------------//
	static bool init(std::string title, int width, int height);

	//Simple clear methods to avoid calling unique_ptr function 
	//outside the class.
	static void clear();

	//Simple swap class to avoid calling a unique_ptr function
	//outside the class.
	static void swap();

	static void resize(int width, int height);

	//Destroys window and context then quit SDL.
	static void quit();

	//------------------------------------------------------//
	//														//
	//					Setters / Getters					//
	//														//
	//------------------------------------------------------//

	//C shaped getter that returns width and height
	//into outside vars via pointers
	static void getSize(int* widthOut, int* heightOut);

	//Returns raw pointer on the window.
	static SDL_Window* getWindowptr();

private:

	//------------------------------------------------------//
	//														//
	//					Private Methods						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Initialize the window and setup everything for the	//
	//	openGL context ang glew initialization				//
	//------------------------------------------------------//	
	static bool initWindow();

	//------------------------------------------------------//
	//	Glew initialization									//
	//------------------------------------------------------//
	static bool initGL();


	static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_window;
	static SDL_GLContext m_GLContext;
	static std::string m_title;
	static int m_winWidth;
	static int m_winHeight;
};

#endif /* PROGRAM_H */