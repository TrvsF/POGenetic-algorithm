#include "agent_manager.h"

agent_manager* agent_manager::s_instance = NULL;

void agent_manager::highlightTopFintess()
{
	agent* topPlace = new agent(VEC2_ONE, NULL);
	float highestFitness = 0.0f;
	for (auto const& agent : m_agents)
	{
		if (agent->getFitness() > highestFitness)
		{
			topPlace = agent;
			highestFitness = agent->getFitness();
		}
	}
	topPlace->shouldHighlight(true);
	printf("top fitness : %.5f\n", topPlace->getFitness());
	doRouletteWheel();
}

void agent_manager::doRouletteWheel()
{
	printf("------------------\n");
	std::list<agent*> sortedAgents;
	// get total fitness
	float totalFitness = 0;
	for (auto const& agnt : m_agents)
	{
		totalFitness += (float) agnt->getFitness();
		sortedAgents.push_back(agnt);
	}
	// sort
	sortedAgents.sort([](agent* lhs, agent* rhs) {return lhs->getFitness() < rhs->getFitness(); });
	// add all to list of pairs
	float tot = 0;
	std::list<std::pair<agent*, float>> agentProbMap;
	for (auto const& agnt : sortedAgents)
	{
		agentProbMap.push_back(std::make_pair(agnt, agnt->getFitness() / totalFitness));
	}
	// TODO : FINISH
	getProbGene(agentProbMap, randomFloat(0, 1));
}

genome* agent_manager::getProbGene(std::list<std::pair<agent*, float>> agentProbMap, float prob)
{
	float tot = 0;
	genome* gen;
	for (auto const& agntPair : agentProbMap)
	{
		if (tot < prob && tot + agntPair.second >= prob)
		{
			printf("found with prob : %.4f", tot);
			return agntPair.first->gnome();
		}
		tot += agntPair.second;
	}
	return nullptr;
}

genome* agent_manager::getCrossoverGene(genome* g1, genome* g2, int crossoverpoint)
{
	genome* newG = new genome();
	genome* activeG = g1;
	for (int i = 0; i < 1000; i++)
	{
		if (i == crossoverpoint)
			activeG = g2;

		newG->setGeneAtIndex(i, g1->getGeneAtIndex(i));
	}
	return newG;
}

agent_manager* agent_manager::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new agent_manager();

	return s_instance;
}

void agent_manager::addAgent(agent* agent)
{
	m_agents.push_back(agent);
}

void agent_manager::startDebugTest()
{
	m_tickCounter = 0;
	for (auto const& agent : m_agents)
	{
		agent->beginSimulation();
	}
}

void agent_manager::stopDebugTest()
{
	for (auto const& agent : m_agents)
	{
		agent->stopSimulation();
		printf("fitness : %.5f\n", agent->getFitness());
	}
}

agent_manager::agent_manager()
{
	m_tickCounter = 0;
	/*
		selection methods to add:
		- https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)#Boltzmann_Selection
	*/
}

agent_manager::~agent_manager()
{
}

void agent_manager::update()
{
	m_tickCounter++;

	if (m_tickCounter == SIM_STEPS)
	{
		printf("stopping test\n");
		stopDebugTest();
		highlightTopFintess();
	}
}
