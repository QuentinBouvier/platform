#include "..\Headers\Window.h"

//Creating an errorlog instance for private use in other classes
Errorlog *errorlog = Errorlog::getInstance();

//Initialize static members
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::m_window = 
		std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::string Window::m_title;
int Window::m_winWidth;
int Window::m_winHeight;
SDL_GLContext Window::m_GLContext;

void Window::quit()
{
	//Clears SDL C Structs
	SDL_GL_DeleteContext(m_GLContext);
	SDL_Window *temp = m_window.release();
	SDL_DestroyWindow(temp);
	SDL_Quit();
}

bool Window::init(std::string title, int width, int height)
{
	//Window Constructor
	m_title = title;
	m_winWidth = width;
	m_winHeight = height;

	if (!initWindow())
	{
		return false;
	}

	if (!initGL())
	{
		return false;
	}
	return true;
}

bool Window::initWindow()
{
	//SDL initialisation
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		errorlog->logError("SDL_init : ", SDL_GetError());
		SDL_Quit();

		return false;
	}

	//Setting up OpenGL version

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Setting up double buffering

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Draw a window in a shared_ptr

	m_window.reset(SDL_CreateWindow(m_title.c_str(),
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							m_winWidth,
							m_winHeight,
							SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));


	if (m_window == 0)
	{
		errorlog->logError("SDL_CreateWindow : ", SDL_GetError());

		SDL_Quit();

		return false;
	}

	//Create an OpenGL context

	m_GLContext = SDL_GL_CreateContext(m_window.get());

	if (m_GLContext == 0)
	{
		errorlog->logError("SDL_GL_CreateContext : ", SDL_GetError);
		SDL_DestroyWindow(m_window.get());
		SDL_Quit();

		return false;
	}

	return true;
}

bool Window::initGL()
{
	//Initialize Glew

	GLenum GLEWInitialization(glewInit());

	if (GLEWInitialization != GLEW_OK)
	{
		errorlog->logError("Glew Initialization Error : ",
						   glewGetErrorString(GLEWInitialization));
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_window.get());
		SDL_Quit();

		return false;
	}

	//glEnable(GL_DEPTH_TEST);

	return true;
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap()
{
	SDL_GL_SwapWindow(m_window.get());
}

void Window::resize(int width, int height)
{
}

void Window::getSize(int* widthOut, int* heightOut)
{
	*widthOut = m_winWidth;
	*heightOut = m_winHeight;
}

SDL_Window* Window::getWindowptr()
{
	return m_window.get();
}
