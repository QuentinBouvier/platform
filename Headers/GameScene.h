#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <list>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLScene.h"
#include "Rectangle.h"
#include "Player.h"
#include "ItemManager.h"

class GameScene :
	public GLScene
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//

	GameScene();
	GameScene(Size size);
	~GameScene();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//
	virtual void mainLoop();
	
private:

	ItemManager m_itemManager;
};

#endif /* GAMESCENE_H */