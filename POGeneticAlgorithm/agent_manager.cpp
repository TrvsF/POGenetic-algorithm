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
	m_totalFitness = 0;
	for (auto const& agnt : m_agents)
	{
		m_totalFitness += (float) agnt->getFitness();
		sortedAgents.push_back(agnt);
	}
	if (m_totalFitness > m_bestFitness)
	{
		m_bestFitnessGen = m_genCounter;
		m_bestFitness = m_totalFitness;
	}
	// sort
	sortedAgents.sort([](agent* lhs, agent* rhs) {return lhs->getFitness() < rhs->getFitness(); });
	// add all to list of pairs
	float tot = 0;
	std::list<std::pair<agent*, float>> agentProbMap; // sorted lowest to highest
	for (auto const& agnt : sortedAgents)
	{
		agentProbMap.push_back(std::make_pair(agnt, agnt->getFitness() / m_totalFitness));
	}
	int count = 0;
	// TODO : FINISH
	for (auto const& agntPair : agentProbMap)
	{
		if (count > 70)
		{
			agntPair.first->gnome(getProbGene(agentProbMap, randomBinary()));
		}
		else
		{
			agntPair.first->gnome(new genome());
		}
		count++;
	}
	startDebugTest();
}

genome* agent_manager::getProbGene(std::list<std::pair<agent*, float>> agentProbMap, float prob)
{
	float tot = 0;
	for (auto const& agntPair : agentProbMap)
	{
		if (tot < prob && tot + agntPair.second >= prob)
		{
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
	m_genCounter++;
	resetPos();
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

void agent_manager::getDebugData(std::string* str)
{
	str[0] = "tick : " + std::to_string(m_tickCounter);
	str[1] = "gen : " + std::to_string(m_genCounter);
	str[2] = "tot fitness : " + std::to_string(m_totalFitness);
	str[3] = "best fitness : " + std::to_string(m_bestFitness) + "|" + std::to_string(m_bestFitnessGen);
}

void agent_manager::resetPos()
{
	for (auto const& agent : m_agents)
	{
		agent->resetPos();
	}
}

agent_manager::agent_manager()
{
	m_genCounter = 0;
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
		m_tickCounter = 0;
	}
}
