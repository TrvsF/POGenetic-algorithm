/*----------
	agent manager class
	handles the mutation and selection of genomes

	a. travis 20th jan
----------*/
#ifndef _AGENTS_H
#define _AGENTS_H

#include "agent.h"
#include "math_helper.h"
#include "genome.h"
#include <iostream>
#include <map>
#include <list>

class agent_manager
{
	private:
		static agent_manager* s_instance;

		const long SIM_STEPS = 999;
		int m_tickCounter;

		void highlightTopFintess();

		void doRouletteWheel();
		genome* getCrossoverGene(genome* g1, genome* g2, int crossoverpoint);

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