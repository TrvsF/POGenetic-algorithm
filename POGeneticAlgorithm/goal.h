/*----------
	graphic engine class
	handles all drawing to screen methods

	a. travis 22nd dec
----------*/
#ifndef _GOAL_H
#define _GOAL_H

#include "game_entity.h"
#include "physics.h"

class goal : public game_entity
{
	private:
	public:
		goal(Vector2 position);
		virtual ~goal();


		void render();
};

#endif