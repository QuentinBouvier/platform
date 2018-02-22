#ifndef PhysicsObject_H
#define PhysicsObject_H

#include <list>

#include <SDL.h>

#include "Shape.h"
#include "Global.h"


class PhysicsObject
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//
	PhysicsObject();
	PhysicsObject(Size size, Position position, float speed, Shape_type shapetype);
	~PhysicsObject();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//

	//Add a force to the force pool
	void addForce(Force force);

	//remove a force from the force pool
	void removeForce(Force force);

	//------------------------------------------------------//
	//														//
	//						  Getters						//
	//														//
	//------------------------------------------------------//

	int getId() const;
	Size getSize() const;
	Shape_type getType() const;
	Position getPos() const;
	Position getPrevPos() const;
	Velocity getVel() const;
	Velocity getMaxSpeed() const;
	Force getForce() const;

	//------------------------------------------------------//
	//														//
	//						  Setters						//
	//														//
	//------------------------------------------------------//

	void setId(int id);
	void setSize(Size size);

	void setPos(Position pos);
	void setprevPos(Position pos);
	void setVel(Velocity velocity);

	//------------------------------------------------------//
	//														//
	//					 Virtual methods					//
	//														//
	//------------------------------------------------------//

	//Calls member display methods
	virtual void display(glm::mat4 const &projection, glm::mat4 const &modelview) = 0;

	//------------------------------------------------------//
	//														//
	//					Static methods						//
	//														//
	//------------------------------------------------------//

	//Compare PhysiscsObjects according to their ID
	static bool compare(PhysicsObject const& a, PhysicsObject const& b);
	static bool compare(PhysicsObject* const &a, PhysicsObject* const &b);

protected:

	Position m_pos;				//Absolute Position
	Position m_prevPos;			//Absolute previous position
	Size m_size;				//Size of the physic relevant area

	Velocity m_maxSpeed;		//Max velocity of the object

	float m_mass;				//Mass of the object
	Force m_forces;				//Forces to apply on the object
	Velocity m_vel;				//Current velocity of the object

	Shape_type m_shapeType;		//Type of the Shape included into the PhysicsObject

	int m_id;					//Id
};

#endif /* PhysicsObject_H */