#include "goal.h"

goal::goal(Vector2 position)
{
	pos(position);

	setTexture("goal.png");

	physics::INSTANCE()->addEntity(this);
}

goal::~goal()
{
}

void goal::render()
{
	renderTexture();
}
