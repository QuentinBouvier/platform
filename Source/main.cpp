#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "../Headers/Errorlog.h"
#include "../Headers/Window.h"
#include "../Headers/GameScene.h"
#include "../Headers/Global.h"

using namespace std;

int main(int argc, char** argv)
{
	Errorlog *errorlog;
	errorlog = Errorlog::getInstance();
	errorlog->setStream(LOG_STREAM);

	if (!Window::init("Awesome Mouthon's Platforming game v0.0a", 800, 600))
		return -1;

	GameScene gamescene(Size(1500, 1500, 200));
	gamescene.mainLoop();

	Window::quit();
	errorlog->kill();
	return 0;
}
