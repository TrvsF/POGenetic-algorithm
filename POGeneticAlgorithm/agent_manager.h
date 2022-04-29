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
#include <fstream>

class agent_manager
{
	private:
		static agent_manager* s_instance;

		std::list<agent*> m_agents;
		std::list<agent*> m_agents2;

		// ------------
		// agent stuff
		bool m_agentFlip;
		agent* m_trackedAgent;

		// ------------
		// config stuff
		bool m_isSimulating;
		long m_ticksPerGen;

		// ------------
		// tracking stuff
		int m_populationSize;
		int m_tickCounter;
		int m_genCounter;

		float m_bestFitness;
		float m_bestFitness2;

		int m_bestFitnessGen;
		int m_bestFitnessGen2;

		void highlightTopFintess();

		void saveAgentInfo(std::list<agent*> sortedAgents, float fitness, int type);

		// ------------
		// alg stuff 
		// bolzmann
		float m_temp;
		void doBolzmann();
		// roulletee
		void doRouletteWheel();
		// general
		void wakeAllAgents();
		void wakeAgent(agent* a);

		void sleepAllAgents();
		void sleepAgent(agent* a);

		genome* getGenomeFromProbMap(std::list<std::pair<agent*, float>> agentProbMap, float prob);
		genome* getCrossoverGenes(genome* g1, genome* g2, int crossoverpoint);
		genome* getCrossoverGene(genome* g, int corssoverpoint);
		

	public:
		static agent_manager* INSTANCE();

		void addAgent(agent* agent);

		void startDebugTest();
		void stopDebugTest();

		const int POPULATION_MULTIPLYER = 15;

		void getDebugData(std::string* str);
		void resetPos();

		// user input
		void pauseResume();
		void onClick(Vector2 mousePos);
		agent* getAgentData();

		agent_manager();
		~agent_manager();

		void update();
};
#endif