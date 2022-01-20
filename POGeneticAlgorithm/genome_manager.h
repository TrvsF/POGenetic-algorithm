/*----------
	genome selector glass
	handles the mutation and selection of genomes

	a. travis 20th jan
----------*/
#ifndef _GENOMES_H
#define _GENOMES_H

#include <iostream>

class genome_manager
{
	private:
		static genome_manager* s_instance;

	public:
		static genome_manager* INSTANCE();

		genome_manager();
		~genome_manager();

};

#endif