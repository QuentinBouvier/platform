#include "..\Headers\Player.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;

Player::Player() :
PhysicsObject(),
m_sprite(),
m_controls()
{
	initControls();
}

Player::Player(Shape &sprite, float speed) :
PhysicsObject(sprite.getSize(),  Position(0.0, 0.0, 0.0), speed, BOX),
m_sprite(&sprite),
m_controls()
{
	initControls();
}


Player::~Player()
{
}

using namespace glm;

void Player::display(mat4 const &projection, mat4 const &modelview)
{
	//update the modelview with the sprite position
	mat4 modelviewTmp = translate(modelview, m_pos);

	//calls sprite display method
	m_sprite->display(projection, modelviewTmp);
}

void Player::moves(Input const &input)
{
	Uint16 direction = NO_MOTION;

	for (int i(0); i < 3; i++)
	{
		if (input.getKey(getKey("moveright", i)))
		{
			direction = (direction | MOTION_RIGHT);
		}

		if (input.getKey(getKey("moveleft", i)))
		{
			direction = (direction | MOTION_LEFT);
		}

		if (input.getKey(getKey("moveup", i)))
		{
			direction = (direction | MOTION_UP);
		}
	}
	motion(direction);
}

void Player::motion(Uint16 dir)
{
	if (dir & MOTION_RIGHT != 0 && !(m_motionApplied & MOTION_RIGHT != 0))
	{
		m_forces += Force(0.0, 2.0, 0.0);
		m_motionApplied = (dir | MOTION_RIGHT);
		std::cout << "right" << std::endl;
	}
	else
	{
		m_forces -= Force(0.0, 2.0, 0.0);
		m_motionApplied = (dir ^ MOTION_RIGHT);
	}

	if (dir & MOTION_LEFT != 0 && !(m_motionApplied & MOTION_LEFT != 0))
	{
		m_forces += Force(0.0, -2.0, 0.0);
		m_motionApplied = (dir | MOTION_LEFT);
		std::cout << "left" << std::endl;
	}
	else
	{
		m_forces -= Force(0.0, -2.0, 0.0);
		m_motionApplied = (dir ^ MOTION_LEFT);
	}

	if (dir & MOTION_UP != 0 && !(m_motionApplied & MOTION_UP != 0))
	{
		m_forces += Force(-2.0, 0.0, 0.0);
		m_motionApplied = (dir | MOTION_UP);
		std::cout << "up" << std::endl;
	}
	else
	{
		m_forces -= Force(-1.0, 0.0, 0.0);
		m_motionApplied = (dir ^ MOTION_UP);
	}
}

using namespace std;

SDL_Scancode Player::getKey(std::string control, Uint8 index)
{
	//initialize the returned key code as UNKNOWN
	SDL_Scancode keyCode(SDL_SCANCODE_UNKNOWN);

	//if control name is incorrect
	if (!m_controls.count(control))
	{
		errorlog->logError("\"", control, "\" is not a control name.");
	}
	//if index is out of bound.
	else if (index > m_controls.count(control))
	{
		errorlog->logError("No index ", index, " for control \"", control, "\"");
	}
	//if control name is correct and exists for this index.
	else
	{
		//find the control series of keys
		pair<controlsIt, controlsIt> result = m_controls.equal_range(control);
		int indexCount(0);
		for (controlsIt it = result.first; it != result.second; ++it)
		{
			//Get the key at the correct index
			if (index == indexCount)
				keyCode = it->second;

			indexCount++;
		}

	}
	return keyCode;
}

using namespace std;

void Player::setControl(std::string control, SDL_Scancode key, Uint8 index)
{
	//Control name is incorrect
	if (!m_controls.count(control))
	{
		errorlog->logError("\"", control, "\" is not a control name.");
	}
	//control index is out of bound
	else if (index > m_controls.count(control))
	{
		errorlog->logError("No index ", index, " for control \"", control, "\"");
	}
	//control index is bigger than the max keys for a control
	else if (index > 2)
	{
		errorlog->logError("There can't be more than 3 different keys for a control");
	}
	else
	{
		//finds the control series of keys
		pair<controlsIt, controlsIt> result = m_controls.equal_range(control);
		int indexCount(0);
		for (controlsIt it = result.first; it != result.second; ++it)
		{
			//sets the new key at the correct index
			if (index == indexCount)
				it->second = key;

			indexCount++;
		}

	}
}

void Player::initControls()
{
	m_controls.insert(controlsPair("moveleft", SDL_SCANCODE_LEFT));
	m_controls.insert(controlsPair("moveleft", SDL_SCANCODE_A));
	m_controls.insert(controlsPair("moveright",SDL_SCANCODE_RIGHT));
	m_controls.insert(controlsPair("moveright", SDL_SCANCODE_D));
	m_controls.insert(controlsPair("moveup", SDL_SCANCODE_UP));
	m_controls.insert(controlsPair("moveup", SDL_SCANCODE_W));
}