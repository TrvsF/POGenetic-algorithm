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

		const int SIM_STEPS = 5000;
		int m_tickCounter;

		std::list<agent*> m_agents;

	public:
		static agent_manager* INSTANCE();

		void addAgent(agent* agent);
		void startDebugTest();
		void stopDebugTest();

		const int POPULATION_MULTIPLYER = 10;

		agent_manager();
		~agent_manager();

		void update();
};
#endif