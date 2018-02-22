#include "..\Headers\PhysicsObject.h"


//------------------------------------------------------//
//														//
//			Class constructors and destructor.			//
//														//
//------------------------------------------------------//

PhysicsObject::PhysicsObject():
m_pos(0.0, 0.0, 0.0),
m_prevPos(0.0, 0.0, 0.0),
m_size(0.0, 0.0, 0.0),
m_maxSpeed(0.0, 0.0, 0.0),
m_mass(0.0),
m_forces(0.0, 0.0, 0.0),
m_vel(0.0, 0.0, 0.0),
m_shapeType(NO_TYPE)
{}

PhysicsObject::PhysicsObject(Size size, Position position, float speed, Shape_type shapetype):
m_pos(position),
m_prevPos(position),
m_size(size),
m_maxSpeed(speed, speed, 0.0),
m_mass(0.0),
m_forces(0.0, 0.0, 0.0),
m_vel(0.0, 0.0, 0.0),
m_shapeType(shapetype)
{
}


PhysicsObject::~PhysicsObject()
{
}

//------------------------------------------------------//
//														//
//					  Public Methods					//
//														//
//------------------------------------------------------//

void PhysicsObject::addForce(Force force)
{
	m_forces += force;
}

void PhysicsObject::removeForce(Force force)
{
	m_forces -= force;
}

//------------------------------------------------------//
//														//
//						  Getters						//
//														//
//------------------------------------------------------//

int PhysicsObject::getId() const
{
	return m_id;
}

Size PhysicsObject::getSize() const
{
	return m_size;
}

Shape_type PhysicsObject::getType() const
{
	return m_shapeType;
}

Position PhysicsObject::getPos() const
{
	return m_pos;
}

Position PhysicsObject::getPrevPos() const
{
	return m_prevPos;
}

Velocity PhysicsObject::getVel() const
{
	return m_vel;
}

Velocity PhysicsObject::getMaxSpeed() const
{
	return m_maxSpeed;
}

Force PhysicsObject::getForce() const
{
	return m_forces;
}

//------------------------------------------------------//
//														//
//						  Setters						//
//														//
//------------------------------------------------------//

void PhysicsObject::setId(int id)
{
	m_id = id;
}

void PhysicsObject::setSize(Size size)
{
	m_size = size;
}

void PhysicsObject::setPos(Position pos)
{
	m_pos = pos;
}

void PhysicsObject::setprevPos(Position pos)
{
	m_prevPos = pos;
}

void PhysicsObject::setVel(Velocity velocity)
{
	m_vel = velocity;
}

//------------------------------------------------------//
//														//
//					Static methods						//
//														//
//------------------------------------------------------//

bool PhysicsObject::compare(PhysicsObject const& a, PhysicsObject const& b)
{
	return a.m_id < b.m_id;
}

bool PhysicsObject::compare(PhysicsObject* const& a, PhysicsObject* const& b)
{
	return a->m_id < b->m_id;
}