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
#include <string>

class agent_manager
{
	private:
		static agent_manager* s_instance;

		const long SIM_STEPS = 999;
		int m_tickCounter;
		int m_genCounter;

		void highlightTopFintess();

		void doRouletteWheel();
		genome* getProbGene(std::list<std::pair<agent*, float>> agentProbMap, float prob);
		genome* getCrossoverGene(genome* g1, genome* g2, int crossoverpoint);

		std::list<agent*> m_agents;

		//debug info
		float m_totalFitness;
		float m_bestFitness;
		int m_bestFitnessGen;

	public:
		static agent_manager* INSTANCE();

		void addAgent(agent* agent);
		void startDebugTest();
		void stopDebugTest();

		const int POPULATION_MULTIPLYER = 10;
		void getDebugData(std::string* str);

		void resetPos();

		agent_manager();
		~agent_manager();

		void update();
};
#endif