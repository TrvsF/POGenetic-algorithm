/*----------
	gene class
	a collection of what the agent is doing at a specfic point in time (or specfic game tick)

	a. travis 20th jan
----------*/
#ifndef _GENE_H
#define _GENE_H

#include "math_helper.h"
#include <string>

class gene
{
	private:
		int m_gene[5];

	public:
		gene(int moveForward, int moveBackward, int turnRight, int turnLeft, int boost);
		gene();
		~gene();

		bool shouldMoveForward();
		bool shouldMoveBackward();
		bool shouldTurnRight();
		bool shouldTrunLeft();
		bool shouldBoost();

		std::string getAsString();
};

#endif