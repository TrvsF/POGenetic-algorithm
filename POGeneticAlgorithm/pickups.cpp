#include "pickups.h"

pickups::pickups(Vector2 position)
{
	setTexture("gold.png");
	pos(Vector2(200,200));
}

pickups:: ~pickups()
{
}

void pickups::update()
{
}

void pickups::render()
{
	renderTexture();
}