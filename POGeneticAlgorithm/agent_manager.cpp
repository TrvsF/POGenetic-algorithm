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

	// save info of agents to file
	saveAgentInfo(sortedAgents);

	// roll 6 times and select 6 agents to stay as is
	int keepGenomes = 5;
	int mutateGenomes = 10;
	int generatedGenomes = m_agents.size() - (keepGenomes + mutateGenomes);

	// new list of agents for the next generation
	std::vector<genome*> newGenomes;
	int count = 0;

	// pick agents to go to next gen unalterd
	for (int i = 0; i < keepGenomes; i++)
	{
		newGenomes.push_back(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)));
		count++;
	}

	// pick 2 agents to mutate
	for (int i = 0; i < mutateGenomes; i++)
	{
		newGenomes.push_back(getCrossoverGene(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), randomInt(0, 1000)));
		count++;
	}

	// repop the rest
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

	newGenomes.clear();
	agentProbMap.clear();
	sortedAgents.clear();
	m_alreadyUsedGenomes.clear();

	printf("done roulette\n");
}

void agent_manager::wakeAllAgents()
{
	for (auto const& agent : m_agents)
	{
		agent->active(true);
	}
	for (auto const& agent : m_agents2)
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
	for (auto const& agent : m_agents2)
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
	genome* newG;
	for (auto const& agentPair : agentProbMap)
	{
		tot += agentPair.second;
		if (prob <= tot)
		{
			newG = agentPair.first->gnome();
			return newG;
		}
	}
	// backup incase something goes *very* wrong
	printf("something has gone very wrong tot : %f\n", tot);
	return new genome();
}

genome* agent_manager::getCrossoverGene(genome* g1, genome* g2, int crossoverpoint)
{
	genome* newG = new genome();
	genome* activeG = g1;
	for (int i = 0; i < 1000; i++)
	{
		if (i == crossoverpoint)
			activeG = g2;

		newG->setGeneAtIndex(i, activeG->getGeneAtIndex(i));
	}
	return newG;
}

void agent_manager::saveAgentInfo(std::list<agent*> sortedAgents)
{
	std::ofstream oFile;
	oFile.open("gene.txt", std::ios_base::app);
	oFile << "----------------\n";
	oFile << "GEN : " << m_genCounter << "\n";
	oFile << "TOT FIT : " << m_totalFitness << "\n";
	for (auto const& agnt : sortedAgents)
	{
		oFile << agnt->getFitness() << "\n";
	}
	oFile.close();
}

agent_manager* agent_manager::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new agent_manager();

	return s_instance;
}

void agent_manager::addAgent(agent* agent)
{
	if (m_agentFlip)
	{
		m_agents.push_back(agent);
	}
	else
	{
		agent->setTexture("enemy2.png");
		m_agents2.push_back(agent);
	}
	m_agentFlip = !m_agentFlip;
}

void agent_manager::startDebugTest()
{
	m_tickCounter = 0;
	m_ticksPerGen = 999;
	m_genCounter++;

	resetPos();
	wakeAllAgents();

	m_isSimulating = true;
}

void agent_manager::stopDebugTest()
{
	m_isSimulating = false;

	sleepAllAgents();
}

void agent_manager::getDebugData(std::string* str)
{
	str[0] = "tick : " + std::to_string(m_tickCounter);
	str[1] = "gen : " + std::to_string(m_genCounter);
	str[2] = "tot fitness : " + std::to_string(m_totalFitness);
	str[3] = "best fitness : " + std::to_string(m_bestFitness) + " : " + std::to_string(m_bestFitnessGen);
}

void agent_manager::resetPos()
{
	for (auto const& agent : m_agents)
	{
		agent->resetPos();
	}
	for (auto const& agent : m_agents2)
	{
		agent->resetPos();
	}
}

void agent_manager::pauseResume()
{
	m_isSimulating = !m_isSimulating;
	printf("%d\n", m_isSimulating);
}

void agent_manager::onClick(Vector2 mousePos)
{
	for (auto const& agent : m_agents)
	{
		BoundingBox agentBB = agent->bb();
		if ((mousePos.y < agentBB.top && mousePos.y > agentBB.bottom) && (mousePos.x < agentBB.left && mousePos.x > agentBB.right))
		{
			m_trackedAgent = agent;
			return;
		}
	}
	for (auto const& agent : m_agents2)
	{
		BoundingBox agentBB = agent->bb();
		if ((mousePos.y < agentBB.top && mousePos.y > agentBB.bottom) && (mousePos.x < agentBB.left && mousePos.x > agentBB.right))
		{
			m_trackedAgent = agent;
			return;
		}
	}
	m_trackedAgent = NULL;
}

agent* agent_manager::getAgentData()
{
	return m_trackedAgent;
}

agent_manager::agent_manager()
{
	m_genCounter = 0;
	m_tickCounter = 0;
	m_bestFitness = 0;
	m_bestFitnessGen = 0;
	m_isSimulating = false;
	m_agentFlip = false;
	m_populationSize = 0;
	m_ticksPerGen = 0;
	m_totalFitness = 0;
	m_trackedAgent = NULL;
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
	if (!m_isSimulating)
		return;

	for (auto const& agent : m_agents)
	{
		agent->update(m_tickCounter);
	}
	for (auto const& agent : m_agents2)
	{
		agent->update(m_tickCounter);
	}

	m_tickCounter++;

	if (m_tickCounter >= m_ticksPerGen)
	{
		stopDebugTest();
		// highlightTopFintess();
		doRouletteWheel();
		startDebugTest();
	}
}