#include "genome_manager.h"

genome_manager* genome_manager::s_instance = NULL;

genome_manager* genome_manager::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new genome_manager();

	return s_instance;
}

genome_manager::genome_manager()
{
	/*
		selection methods to add:
		- https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)#Boltzmann_Selection
	*/
}

genome_manager::~genome_manager()
{
}
