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
#include <vector>
#include <string>
#include <utility>

class agent_manager
{
	public:
		enum class SimState { Inactive, Roullete, SomethingElse };

	private:
		static agent_manager* s_instance;

		std::list<agent*> m_agents;

		std::list<genome*> m_alreadyUsedGenomes;

		// ------------
		// config stuff
		bool m_isSimulating;
		SimState m_state;
		long m_ticksPerGen;

		// ------------
		// tracking stuff
		int m_populationSize;
		int m_tickCounter;
		int m_genCounter;
		float m_totalFitness;
		float m_bestFitness;
		int m_bestFitnessGen;

		void highlightTopFintess();

		// ------------
		// alg stuff 
		// roulletee
		void doRouletteWheel();
		// general
		void wakeAllAgents();
		void wakeAgent(agent* a);
		void sleepAllAgents();
		void sleepAgent(agent* a);
		genome* getGenomeFromProbMap(std::list<std::pair<agent*, float>> agentProbMap, float prob);
		genome* getCrossoverGene(genome* g1, genome* g2, int crossoverpoint);

	public:
		static agent_manager* INSTANCE();

		void state(SimState s);

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