#ifndef Player_H
#define Player_H

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <map>

#include "PhysicsObject.h"
#include "Rectangle.h"
#include "Input.h"

class Player :
	public PhysicsObject
{

public:
	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Default constructor defines no shape as sprite		//
	//	and initilizes default controls						//
	//------------------------------------------------------//
	Player();

	//------------------------------------------------------//
	//	Defines a shape as the sprite and a moving speed	//
	//------------------------------------------------------//
	Player(Shape &sprite, float speed);

	~Player();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Call the Shape sprite display methods after	having	//
	//	calculated the position with internal position		//
	//	member												//
	//------------------------------------------------------//
	void display(glm::mat4 const &projection, glm::mat4 const &modelview);

	//------------------------------------------------------//
	//	Defines the moving controls effects on the sprite	//
	//------------------------------------------------------//
	void moves(Input const &input);

	void motion(Uint16 dir);

	void jump();

	//------------------------------------------------------//
	//														//
	//						 getters						//
	//														//
	//------------------------------------------------------//
	
	int getSpeed() const;

	//------------------------------------------------------//
	//	returns a the key scancode for the defined control	//
	//	Controls are defined by a std::string.				//
	//	index is the index of the key for that control name	//
	//	Controls:											//
	//	"moveleft"											//
	//	"moveright"											//
	//------------------------------------------------------//
	SDL_Scancode getKey(std::string control, Uint8 index);

	//------------------------------------------------------//
	//	returns the name of the control using the key		//
	//	scancode used as argument							//
	//------------------------------------------------------//
	std::string getControl(SDL_Scancode key) const;

	//------------------------------------------------------//
	//														//
	//						 Setters						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Set a key scancode as used for the control name		//
	//	passed on first argument							//
	//	max index is 3										//
	//	index is the index of the key to be changed for the	//
	//	control												//
	//------------------------------------------------------//
	void setControl(std::string control, SDL_Scancode key, Uint8 index);

	void setSpeed(float speed);
	void setColor(glm::vec3 color);

private:

	//------------------------------------------------------//
	//														//
	//					  Private Methods					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Initialize default controls							//
	//------------------------------------------------------//
	void initControls();

	//------------------------------------------------------//
	//														//
	//						 Members						//
	//														//
	//------------------------------------------------------//

	Shape *m_sprite;

	Uint16 m_motionApplied;

	std::multimap<std::string, SDL_Scancode> m_controls;
};

typedef std::pair<std::string, SDL_Scancode> controlsPair;
typedef std::map<std::string, SDL_Scancode>::iterator controlsIt;

#endif /* Player_H */