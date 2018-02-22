#include "..\Headers\GameScene.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;

GameScene::GameScene():
GLScene(),
m_itemManager(m_sceneSize)
{
}

GameScene::GameScene(Size size) :
GLScene(size),
m_itemManager(size)
{}

GameScene::~GameScene()
{
}

void GameScene::mainLoop()
{

	using namespace glm;

	//framerate presets

	Uint32 frameRate(1000 / 60);
	Uint32 loopStart(0), loopEnd(0), loopElapsed(0);

	//3D Presets
	mat4 projection;
	mat4 modelview;

	//gets Window Size
	int winWidth, winHeight;
	Window::getSize(&winWidth, &winHeight);

	//Inits matrices for 3D rendering
	projection = perspective(70.0, (double) winWidth / winHeight, 1.0, 1000.0);
	modelview = mat4(1.0);

	//Init the rectangle to be used as a player Shape
	Rectangle rec(100.0, 75.0, "Shaders/3DColor.vert", "Shaders/3DColor.frag", 1.0, 0.0, 1.0);
	rec.load();

	//Create player with rec as sprite
	Player player(rec, 7.0f);

	//init and fill itemManager
	m_itemManager.init(1000/60, Force(0.0, -1.0, 0.0), projection, modelview);
	m_itemManager.addItem(player);

	//Draw loop
	while (!m_inputs.getWindowClosingEvent())
	{

		loopStart = SDL_GetTicks();
		//Query events
		m_inputs.updateEvents();

		//Quitting input query
		if (m_inputs.getKey(SDL_SCANCODE_ESCAPE))
			break;

		//Query player moving inputs
		player.moves(m_inputs);
		m_itemManager.timestep();

		//Cleans the screen
		Window::clear();

		//Camera setting
		modelview = lookAt(vec3(0, 0, 1000), vec3(0, 0, 0), vec3(0, 1, 0));

		//Displays
		m_itemManager.setModelview(modelview);
		m_itemManager.display();


		//Actualizes the window
		Window::swap();

		//Elapsed time in loop

		loopEnd = SDL_GetTicks();
		loopElapsed = loopEnd - loopStart;

		//Complete Elapsed time to fill framerate requirement.

		if (loopElapsed < frameRate)
			SDL_Delay(frameRate - loopElapsed);
	}
}


//------------------------------------------------------//
//														//
//					Setters / Getters					//
//														//
//------------------------------------------------------//
