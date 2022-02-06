/*----------
	genome class
	a collection of genes 

	a. travis 20th jan
----------*/
#ifndef _GENOME_H
#define _GENOME_H

#include "gene.h"

class genome
{
	private:
		const int SIZE = 1000;

		gene* m_genome[1000];

	public:
		genome();
		~genome();

		gene* getGeneAtIndex(int i);
		void setGeneAtIndex(int i, gene* g);

		void populate();
};

#endif