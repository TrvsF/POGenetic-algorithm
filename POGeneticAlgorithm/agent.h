/*----------
	agent class
	the test subject

	a. travis 23rd dec - updated 20th Jan
----------*/
#ifndef _AGENT_H
#define _AGENT_H

#include "game_entity.h"
#include "physics.h"
#include "genome.h"
#include <iostream>

class agent : public game_entity
{
	private:
		/*----------
			MOVEMENT
		----------*/
		const int BOOST_COOLDOWN = 210; // ammount of frames until can boost again
		const float MAX_VEL = 2.6f; // max normal velocity without boost
		const float MAX_VEL_BOOST = 7.5f; // max boosted velocity
		const float BOOST_MUL[3] = { 2.1f, 2.2f, 1.2f }; // how fast you are boosted dependent of if you're turning
		// ^ lower values mean that you have to spam space more for it to work

		float m_tickVelocity;

		int m_boostCooldownCount;
		int m_boostIndex;
		int m_projCount;

		bool m_hasBoosted;
		bool m_canBoost;

		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();

		void boost();
		void checkBoostCooldown();
		void cancelBoost();

		void doQrterStepMovement();

		Vector2 getMovementVector();
		float calcVelocity();

		void movePlayer(Vector2 movementVec);

		/*----------
			GA
		----------*/
		int m_simStep;

		genome* m_genome;

		void handleGeneInputs();

	public:
		agent(Vector2 position);
		virtual ~agent();

		genome* gnome();
		void gnome(genome* g);

		void beginSimulation();
		void stopSimulation();

		void update();
		void render();
};

#endif