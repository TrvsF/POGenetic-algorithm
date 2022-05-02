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

void agent_manager::doBolzmann()
{
	// list of sorted agents
	std::list<agent*> sortedAgents;

	// get total fitness of population
	float totalFitness = 0;
	for (auto const& agnt : m_agents2)
	{
		totalFitness += (float)agnt->getFitness();
		sortedAgents.push_back(agnt);
	}

	// menu stuff
	if (totalFitness > m_bestFitness2)
	{
		m_bestFitnessGen2 = m_genCounter;
		m_bestFitness2 = totalFitness;
	}

	// sort the agents by fitness
	sortedAgents.sort([](agent* lhs, agent* rhs) {return lhs->getFitness() < rhs->getFitness(); });

	// add agents along with their fitness/total fitness to a pairmap
	float tot = 0;
	std::list<std::pair<agent*, float>> agentProbMap; // sorted lowest to highest
	for (auto const& agnt : sortedAgents)
	{
		agentProbMap.push_back(std::make_pair(agnt, agnt->getFitness() / totalFitness));
	}

	// save info of agents to file
	saveAgentInfo(sortedAgents, totalFitness, 1);

	// 0.039 = benchmark
	// 0.1 = max
	// higher the temp the more likely to keep population the same
	if (totalFitness < 0.037)
	{
		m_temp = 0;
	}
	else
	{
		m_temp = std::fmin(std::powf(1.15f, totalFitness) - 0.963, 0.9f);
	}

	int newPop = std::round((1 - m_temp) * sortedAgents.size());
	int oldPop = sortedAgents.size() - newPop;

	// new list of agents for the next generation
	std::vector<genome*> newGenomes;

	// pick agents to go to next gen unalterd
	for (int i = 0; i < newPop; i++)
	{
		genome* newGenome = new genome();
		newGenome->populate();
		newGenomes.push_back(newGenome);
	}

	for (int i = 0; i < oldPop; i++)
	{
		if (randomBinary())
			newGenomes.push_back(getCrossoverGene(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), randomInt(0, 500)));
		else
			newGenomes.push_back(getCrossoverGenes(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), randomInt(0, 500)));
	}

	// give new genomes and cleanup
	agentProbMap.clear();
	sortedAgents.clear();

	int count = 0;
	for (auto const& agent : m_agents2)
	{
		agent->gnome()->deleteGenes();
		delete agent->gnome();
		agent->gnome(newGenomes[count]);
		count++;
	}

	newGenomes.clear();
	
	printf("newPop : %d\ntemp : %f\n", newPop, m_temp);
}

void agent_manager::doRouletteWheel()
{
	// list of sorted agents
	std::list<agent*> sortedAgents;

	// get total fitness of population
	float totalFitness = 0;
	for (auto const& agnt : m_agents)
	{
		totalFitness += (float) agnt->getFitness();
		sortedAgents.push_back(agnt);
	}

	// menu stuff
	if (totalFitness > m_bestFitness)
	{
		m_bestFitnessGen = m_genCounter;
		m_bestFitness = totalFitness;
	}

	// sort the agents by fitness
	sortedAgents.sort([](agent* lhs, agent* rhs) {return lhs->getFitness() < rhs->getFitness(); });

	// add agents along with their fitness/total fitness to a pairmap
	float tot = 0;
	std::list<std::pair<agent*, float>> agentProbMap; // sorted lowest to highest
	for (auto const& agnt : sortedAgents)
	{
		agentProbMap.push_back(std::make_pair(agnt, agnt->getFitness() / totalFitness));
	}

	// save info of agents to file
	saveAgentInfo(sortedAgents, totalFitness, 0);

	// roll 6 times and select 6 agents to stay as is
	int keepGenomes = 10;
	int mutateGenomes = 5;
	int mutateRandGeneomes = 5;
	int generatedGenomes = m_agents.size() - (keepGenomes + mutateGenomes + mutateRandGeneomes);

	// new list of agents for the next generation
	std::vector<genome*> newGenomes;

	// pick agents to go to next gen unalterd
	for (int i = 0; i < keepGenomes; i++)
	{
		newGenomes.push_back(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)));
	}

	// pick 2 agents to mutate
	for (int i = 0; i < mutateGenomes; i++)
	{
		newGenomes.push_back(getCrossoverGenes(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), randomInt(0, 500)));
	}

	for (int i = 0; i < mutateRandGeneomes; i++)
	{
		newGenomes.push_back(getCrossoverGene(getGenomeFromProbMap(agentProbMap, randomFloat(0, 1)), randomInt(0, 500)));
	}

	// repop the rest
	for (int i = 0; i < generatedGenomes; i++)
	{
		genome* newGenome = new genome();
		newGenome->populate();
		newGenomes.push_back(newGenome);
	}

	// give new genomes and cleanup
	agentProbMap.clear();
	sortedAgents.clear();

	bool shouldDelete = false;
	int count = 0;
	for (auto const& agent : m_agents)
	{
		agent->gnome()->deleteGenes();
		delete agent->gnome();

		agent->gnome(newGenomes[count]);
		count++;
	}

	newGenomes.clear();

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

void agent_manager::sleepAgent(agent* a)
{
	a->active(false);
}

genome* agent_manager::getGenomeFromProbMap(std::list<std::pair<agent*, float>> agentProbMap, float prob)
{
	genome* newGenome = new genome();
	float tot = 0;
	for (auto const& agentPair : agentProbMap)
	{
		tot += agentPair.second;
		if (prob <= tot)
		{		
			for (int i = 0; i < 500; i++)
			{
				newGenome->setGeneAtIndex(i, new gene(*agentPair.first->gnome()->getGeneAtIndex(i)));
			}
			return newGenome;
		}
	}
	newGenome->populate();
	return newGenome;
}

// takes 2 parent genes and a corssover point
// outputs new gene with parent genes
genome* agent_manager::getCrossoverGenes(genome* g1, genome* g2, int crossoverpoint)
{
	genome* newGenome = new genome();
	genome* activeGenome = g1;
	for (int i = 0; i < 500; i++)
	{
		if (i == crossoverpoint)
			activeGenome = g2;

		newGenome->setGeneAtIndex(i, new gene(*activeGenome->getGeneAtIndex(i)));
	}
	return newGenome;
}

// takes in 1 parent gene and a crossover point
// outputs new gene with parent gene and random genes
genome * agent_manager::getCrossoverGene(genome * g, int corssoverpoint)
{
	genome* newGenome = new genome();
	bool isFromGene = randomBinary();
	for (int i = 0; i < 500; i++)
	{
		if (i == corssoverpoint)
			isFromGene = !isFromGene;

		if (isFromGene)
		{
			newGenome->setGeneAtIndex(i, new gene(*g->getGeneAtIndex(i)));
		}
		else
		{
			newGenome->setGeneAtIndex(i, new gene());
		}
	}
	return newGenome;
}

std::string agent_manager::getCurrentTimeForFileName()
{
	auto time = std::time(nullptr);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&time), "%F_%T"); // ISO 8601 without timezone information.
	auto s = ss.str();
	std::replace(s.begin(), s.end(), ':', '-');
	return s;
}

void agent_manager::saveAgentInfo(std::list<agent*> sortedAgents, float fitness, int type)
{
	std::ofstream oFile;

	float bestFitness = 0;
	float worstFitness = 1;
	float avgFitness = fitness / sortedAgents.size();
	for (auto const& agnt : sortedAgents)
	{
		float agntFitness = agnt->getFitness();
		if (agntFitness > bestFitness)
		{
			bestFitness = agntFitness;
		}
		if (agntFitness < worstFitness)
		{
			worstFitness = agntFitness;
		}
	}

	oFile.open(m_fileName, std::ios_base::app);
	oFile << "----------------\n";
	oFile << type << "\n"; // type of selection
	oFile << m_genCounter << "\n"; // gen
	oFile << fitness << "\n"; // total fitness
	oFile << bestFitness << "\n"; // best fitness
	oFile << avgFitness << "\n"; // avg fitness
	oFile << worstFitness << "\n"; // worst fitness

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
	m_ticksPerGen = 500;
	m_genCounter++;

	resetPos();
	wakeAllAgents();

	printf("starting gen %d with pop %d\n", m_genCounter, m_agents.size() + m_agents2.size());

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
	str[2] = "best fitness : " + std::to_string(m_bestFitness) + " : " + std::to_string(m_bestFitnessGen);
	str[3] = "best fitness2 : " + std::to_string(m_bestFitness2) + " : " + std::to_string(m_bestFitnessGen2);
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
	m_bestFitness2 = 0;
	m_bestFitnessGen2 = 0;
	m_isSimulating = false;
	m_agentFlip = false;
	m_populationSize = 0;
	m_ticksPerGen = 0;
	m_trackedAgent = NULL;
	m_fileName = "gene-" + getCurrentTimeForFileName() + ".txt";
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
		doBolzmann();
		startDebugTest();
	}
}