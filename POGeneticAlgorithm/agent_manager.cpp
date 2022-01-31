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
	printf("fitness : %.5f\n", topPlace->getFitness());
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

	if (m_tickCounter == 2500)
	{
		printf("stopping test\n");
		stopDebugTest();
		highlightTopFintess();
	}
}
