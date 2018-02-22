#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <iostream>
#include <list>
#include <map>

#include <glm/glm.hpp>

#include "PhysicsObject.h"

class ItemManager
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//

	ItemManager(Size size);
	ItemManager(ItemManager const& source);
	~ItemManager();

	//------------------------------------------------------//
	//														//
	//					 Public Methods						//
	//														//
	//------------------------------------------------------//

	//Calls position calculation methods
	void timestep();

	//call display method for every PhysicsObject in the item map
	void display();

	//Initialize timestep and gravity
	void init(float timestep, Force gravity, glm::mat4 const& projection, glm::mat4 const& modelview);

private:

	//------------------------------------------------------//
	//														//
	//					Private methods						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Applies Verlet integration of equations of motion 	//
	//	for each item in the item Map. Constrain their		//
	//	speed to m_maxspeed									//
	//------------------------------------------------------//
	void verlet();

	//------------------------------------------------------//
	//	Add m_gravity and every force in the item force		//
	//	pool to the acceleration variable of the verlet		//
	//	integration.										//
	//------------------------------------------------------//
	Force accumulateForces(std::list<PhysicsObject*>::iterator it);

	//------------------------------------------------------//
	//	Queries and applies every constraint to satisfy		//
	//	between items of the item map						//
	//------------------------------------------------------//
	void satisfyConstraint();

public:

	//------------------------------------------------------//
	//														//
	//					 Public Methods						//
	//														//
	//------------------------------------------------------//

	//adds and item in the item map
	void addItem(PhysicsObject &item);

	//remove an item from the item map
	void removeItem(int id);

	//------------------------------------------------------//
	//														//
	//						 Setters						//
	//														//
	//------------------------------------------------------//

	void setTimestep(float timestep);
	void setGravity(Force gravity);
	void setProjection(glm::mat4 projection);
	void setModelview(glm::mat4 modelview);

private:

	float m_timestep;						//Frequency of integration steps calculation
	Force m_gravity;						//Gravity force o be applied each step

	glm::mat4 m_projection;
	glm::mat4 m_modelview;

	Size m_size;							//size of the area to be treated
	std::list<PhysicsObject*> m_itemMap;	//map of items in the physics pool

};

typedef std::list<PhysicsObject*>::iterator itemMapIt;

#endif /* ITEMMANAGER_H */