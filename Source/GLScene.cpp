#include "../Headers/GLScene.h"
#include "../Headers/GameScene.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;


//------------------------------------------------------//
//														//
//			Class constructor and destructor.			//
//														//
//------------------------------------------------------//

GLScene::GLScene()
{
}

GLScene::GLScene(Size size) :
m_sceneSize(size)
{}

GLScene::~GLScene()
{
}

//------------------------------------------------------//
//														//
//					Public Methods						//
//														//
//------------------------------------------------------//

//------------------------------------------------------//
//														//
//					Setters / Getters					//
//														//
//------------------------------------------------------//
