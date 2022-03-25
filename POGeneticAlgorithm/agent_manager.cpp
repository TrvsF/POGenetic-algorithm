#include "agent_manager.h"

agent_manager* agent_manager::s_instance = NULL;

void agent_manager::highlightTopFintess()
{
	for (auto const& agent : m_agents)
	{
		agent->shouldHighlight(false);
	}

	agent* topPlace = NULL;
	float highestFitness = 0.0f;
	for (auto const& agent : m_agents)
	{
		if (agent->getFitness() > highestFitness)
		{
			topPlace = agent;
			highestFitness = agent->getFitness();
		}
	}
	if (topPlace != NULL)
	{
		topPlace->shouldHighlight(true);
	}
}

void agent_manager::doRouletteWheel()
{
	// list of sorted agents
	std::list<agent*> sortedAgents;

	// get total fitness of population
	m_totalFitness = 0;
	for (auto const& agnt : m_agents)
	{
		m_totalFitness += (float) agnt->getFitness();
		sortedAgents.push_back(agnt);
	}

	// menu stuff
	if (m_totalFitness > m_bestFitness)
	{
		m_bestFitnessGen = m_genCounter;
		m_bestFitness = m_totalFitness;
	}


	// sort the agents by fitness
	sortedAgents.sort([](agent* lhs, agent* rhs) {return lhs->getFitness() < rhs->getFitness(); });

	// add agents along with their fitness/total fitness to a pairmap
	float tot = 0;
	std::list<std::pair<agent*, float>> agentProbMap; // sorted lowest to highest
	for (auto const& agnt : sortedAgents)
	{
		agentProbMap.push_back(std::make_pair(agnt, agnt->getFitness() / m_totalFitness));
	}

	// roll 6 times and select 6 agents to stay as is
	int keepGenomes = 6;
	int mutateGenomes = 0;
	int generatedGenomes = static_cast<int>(m_agents.size()) - (keepGenomes + mutateGenomes);

	// new list of agents for the next generation
	std::vector<genome*> newGenomes;
	int count = 0;

	// pick agents to go to next gen unalterd
	for (int i = 0; i < keepGenomes; i++)
	{
		newGenomes.push_back(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)));
		count++;
	}

	for (int i = 0; i < mutateGenomes; i++)
	{
		newGenomes.push_back(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)));
		count++;
	}

	for (int i = 0; i < generatedGenomes; i++)
	{
		newGenomes.push_back(new genome());
		count++;
	}

	count = 0;
	for (auto const& agent : m_agents)
	{
		agent->gnome(newGenomes[count]);
		count++;
	}

	agentProbMap.clear();
	sortedAgents.clear();
	m_alreadyUsedGenomes.clear();

	printf("done\n");
}

void agent_manager::wakeAllAgents()
{
	for (auto const& agent : m_agents)
	{
		agent->active(true);
	}
}

void agent_manager::wakeAgent(agent * a)
{
	a->active(true);
}

void agent_manager::sleepAllAgents()
{
	for (auto const& agent : m_agents)
	{
		agent->active(false);
	}
}

void agent_manager::sleepAgent(agent * a)
{
	a->active(false);
}

genome* agent_manager::getGenomeFromProbMap(std::list<std::pair<agent*, float>> agentProbMap, float prob)
{
	float tot = 0;
	genome* newG = new genome();
	for (auto const& agentPair : agentProbMap)
	{
		if (prob <= tot)
		{
			// checks if genome has already been assigned, if so try again
			for (auto const& gnome : m_alreadyUsedGenomes)
			{
				if (gnome == agentPair.first->gnome())
				{
					return getGenomeFromProbMap(agentProbMap, randomFloat(0, 1));
				}
			}
			m_alreadyUsedGenomes.push_back(agentPair.first->gnome());
			return agentPair.first->gnome();
		}
		tot += agentPair.second;
	}
	return newG;
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

void agent_manager::state(SimState s)
{
	m_state = s;
}

void agent_manager::addAgent(agent* agent)
{
	m_agents.push_back(agent);
}

void agent_manager::startDebugTest()
{
	m_state = SimState::Roullete;
	m_tickCounter = 0;
	m_ticksPerGen = 999;
	m_genCounter++;
	resetPos();
	wakeAllAgents();
}

void agent_manager::stopDebugTest()
{
	m_state = SimState::Inactive;
	sleepAllAgents();
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
	m_state = SimState::Inactive;
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
	switch (m_state)
	{
		case SimState::Inactive:
			return;
		case SimState::Roullete:
			for (auto const& agent : m_agents)
			{
				agent->update(m_tickCounter);
			}
			m_tickCounter++;
			if (m_tickCounter >= m_ticksPerGen)
			{
				stopDebugTest();
				highlightTopFintess();
				doRouletteWheel();
				startDebugTest();
			}
			break;
	}
	
}
