#include "physics.h"
#include <typeinfo>

physics* physics::s_instance = NULL;

physics* physics::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new physics();

	return s_instance;
}

void physics::addEntity(game_entity* entity)
{
	m_collisonEnties.push_back(entity);
	m_gameEntities.push_back(entity);
}

void physics::addEntityNoCollison(game_entity* entity)
{
	m_gameEntities.push_back(entity);
}

void physics::translateEntitiesNotPlayer(Vector2 vector)
{
	for (auto const& entity : m_gameEntities)
	{
		entity->translate(vector);
	}
}

bool physics::isGoingToCollideWithBB(BoundingBox playerBB)
{		
	for (auto const& entity : m_collisonEnties)
	{
		if (entity == nullptr)
			continue;

		if (playerBB.isColliding(entity->bb()))
		{
			return true;
		}		
	}

	return false;
}

physics::physics()
{
}

physics::~physics()
{
}