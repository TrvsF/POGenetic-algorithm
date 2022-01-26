#include "agent_manager.h"

agent_manager* agent_manager::s_instance = NULL;

agent_manager* agent_manager::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new agent_manager();

	return s_instance;
}

agent_manager::agent_manager()
{
	/*
		selection methods to add:
		- https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)#Boltzmann_Selection
	*/
}

agent_manager::~agent_manager()
{
}
