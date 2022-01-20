/*----------
	gene class
	a collection of what the agent is doing at a specfic point in time (or specfic game tick)

	a. travis 20th jan
----------*/
#ifndef _GENE_H
#define _GENE_H

class gene
{
	private:

	public:
		gene(int moveForward, int moveBackward, int turnRight, int turnLeft, int boost);
		~gene();

		int m_gene[5];
};

#endif