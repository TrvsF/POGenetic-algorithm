/*----------
	agent manager class
	handles the mutation and selection of genomes

	a. travis 20th jan
----------*/
#ifndef _AGENTS_H
#define _AGENTS_H

#include "agent.h"
#include <iostream>

class agent_manager
{
	private:
		static agent_manager* s_instance;

		agent* m_agents;

	public:
		static agent_manager* INSTANCE();

		const int POPULATION_MULTIPLYER = 10;

		agent_manager();
		~agent_manager();


};

#endif