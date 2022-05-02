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
		const int SIZE = 500;

		gene* m_genome[500];

	public:
		genome();
		~genome();

		gene* getGeneAtIndex(int i);
		void setGeneAtIndex(int i, gene* g);

		void deleteGenes();
		void populate();
};

#endif