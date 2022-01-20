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
		gene* m_genome[1000];

	public:
		genome();
		~genome();

		void populate();
};

#endif