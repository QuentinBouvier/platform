#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <list>

#include "GLScene.h"
#include "Global.h"

class SceneManager
{
public:

	SceneManager();
	~SceneManager();

private:

	std::list<GLScene> scenePile;
};

#endif /* SCENEMANAGER_H */