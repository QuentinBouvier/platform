#include "..\Headers\ItemManager.h"


ItemManager::ItemManager(Size size) :
m_size(size),
m_gravity(Force(0,0,0)),
m_timestep(0),
m_itemMap(0)
{}

ItemManager::ItemManager(ItemManager const& source):
m_size(source.m_size),
m_gravity(source.m_gravity),
m_timestep(source.m_timestep),
m_itemMap(0)
{
	using namespace std;

	//Copies itemMap
	list<PhysicsObject*>::const_iterator sourceit;
	list<PhysicsObject*>::iterator it = m_itemMap.begin();
	for (sourceit = source.m_itemMap.begin(); sourceit != source.m_itemMap.end(); ++sourceit)
	{
		*it = *sourceit;
		++it;
	}
}


ItemManager::~ItemManager()
{
	m_itemMap.clear();
}

void ItemManager::init(float timestep, Force gravity, glm::mat4 const& projection, glm::mat4 const& modelview)
{
	m_timestep = timestep;
	m_gravity = gravity;
	m_projection = projection;
	m_modelview = modelview;
}

/*void ItemManager::checkCollisions()
{
	using namespace std;

	list<PhysicsObject*>::iterator it_testingItem = m_itemMap.begin();
	list<PhysicsObject*>::iterator it_itemToTest = m_itemMap.begin();

	for (it_testingItem; it_testingItem != m_itemMap.end(); ++it_testingItem)
	{
		for (++it_itemToTest; it_itemToTest != m_itemMap.end(); ++it_itemToTest)
		{
			//test testingItem area with itemToTest area and detect collision on every axis
			//set an opposite force on collision axis for testingItem and itemToTest
		}
		it_itemToTest = ++it_testingItem;
	}
}*/

void ItemManager::timestep()
{
	verlet();
	satisfyConstraint();
}

void ItemManager::display()
{
	itemMapIt it_itemList = m_itemMap.begin();

	glm::vec4 tempPos, relativeSize;

	for (it_itemList; it_itemList != m_itemMap.end(); ++it_itemList)
	{
		(*it_itemList)->display(m_projection, m_modelview);
	}
}

void ItemManager::verlet()
{
	itemMapIt it_itemList = m_itemMap.begin();

	for (it_itemList; it_itemList != m_itemMap.end(); ++it_itemList)
	{
		Position x = (*it_itemList)->getPos();
		Position prevX = (*it_itemList)->getPrevPos();
		Force a = accumulateForces(it_itemList);
		float dt = m_timestep;

		(*it_itemList)->setVel(x - prevX + a*dt*dt);

		if ((*it_itemList)->getVel().x >= (*it_itemList)->getMaxSpeed().x)
		{
			(*it_itemList)->setVel(Velocity((*it_itemList)->getMaxSpeed().x, (*it_itemList)->getVel().y, 0.0));
		}
		if ((*it_itemList)->getVel().y >= (*it_itemList)->getMaxSpeed().y)
		{
			(*it_itemList)->setVel(Velocity((*it_itemList)->getVel().x, (*it_itemList)->getMaxSpeed().y, 0.0));
		}
		if ((*it_itemList)->getVel().x <= -1 * (*it_itemList)->getMaxSpeed().x)
		{
			(*it_itemList)->setVel(Velocity(-1 * (*it_itemList)->getMaxSpeed().x, (*it_itemList)->getVel().y, 0.0));
		}
		if ((*it_itemList)->getVel().y <= -1 * (*it_itemList)->getMaxSpeed().y)
		{
			(*it_itemList)->setVel(Velocity((*it_itemList)->getVel().x, -1 * (*it_itemList)->getMaxSpeed().y, 0.0));
		}

		prevX = x;
		x += (*it_itemList)->getVel();

		(*it_itemList)->setPos(x);
		(*it_itemList)->setprevPos(prevX);
	}
}

Force ItemManager::accumulateForces(itemMapIt it)
{
	Force a(0.0, 0.0, 0.0);

	return (a + m_gravity + (*it)->getForce());
}

void ItemManager::satisfyConstraint()
{
	itemMapIt it_itemList = m_itemMap.begin();

	glm::vec4 tempPos, relativeSize;

	for (it_itemList; it_itemList != m_itemMap.end(); ++it_itemList)
	{

		relativeSize = m_projection * m_modelview * glm::vec4((*it_itemList)->getSize(), 1.0);
		tempPos = m_projection * m_modelview * glm::vec4((*it_itemList)->getPos(), 1.0);

		//std::cout << "x = " << relativeSize.x << "; " << "y = " << relativeSize.y << std::endl;

		float absmodelview = glm::abs(m_modelview[3].z);
		//std::cout << absmodelview << std::endl;

		if (tempPos.y <= relativeSize.y / 2 - absmodelview)
		{
			(*it_itemList)->setPos(glm::vec3((*it_itemList)->getPos().x, (*it_itemList)->getPrevPos().y, 0.0)); //x = prevX
		}
		if (tempPos.x >= absmodelview - relativeSize.x / 2)
		{
			(*it_itemList)->setPos(glm::vec3((*it_itemList)->getPrevPos().x, (*it_itemList)->getPos().y, 0.0)); //x = prevX
		}
		//std::cout << "Force on x axis" << (*it_itemList)->getForce().x << std::endl;
	}
}

void ItemManager::addItem(PhysicsObject &item)
{
	using namespace std;

	//Iterator initialized at the beginning of the list
	list<PhysicsObject*>::iterator it = m_itemMap.begin();
	//To start from 0, last id has to be -1
	int lastId = 0;

	//Check if there's a missing id in the list
	while (!m_itemMap.empty() && it != m_itemMap.end() && (*it)->getId() == lastId + 1)
	{
		lastId = (*it)->getId();
		it++;
	}

	//Add new item at the matched id
	it = m_itemMap.insert(it, &item);
	(*it)->setId(distance(m_itemMap.begin(), it) + 1 );

	//Sort list by id
	bool (*compareFunct)(PhysicsObject* const&, PhysicsObject* const&) = PhysicsObject::compare;
	m_itemMap.sort(compareFunct);
}

void ItemManager::removeItem(int id)
{
	using namespace std;

	list<PhysicsObject*>::iterator it = m_itemMap.begin();

	for (int i(0); i < id; i++)
	{
		++it;
	}
	
	(*it) = nullptr;
	m_itemMap.erase(it);
}

void ItemManager::setProjection(glm::mat4 projection)
{
	m_projection = projection;
}
void ItemManager::setModelview(glm::mat4 modelview)
{
	m_modelview = modelview;
}