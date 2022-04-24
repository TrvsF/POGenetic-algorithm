#include "gene.h"

gene::gene(int moveForward, int moveBackward, int turnRight, int turnLeft, int boost)
{
	m_gene[0] = moveForward;
	m_gene[1] = moveBackward;
	m_gene[2] = turnRight;
	m_gene[3] = turnLeft;
	m_gene[4] = boost;
}

gene::gene()
{
	for (int i = 0; i < 5; i++)
	{
		m_gene[i] = randomBinary();
	}
}

gene::~gene()
{
}

bool gene::shouldMoveForward()
{
	return m_gene[0];
}

bool gene::shouldMoveBackward()
{
	return m_gene[1];
}

bool gene::shouldTurnRight()
{
	return m_gene[2];
}

bool gene::shouldTrunLeft()
{
	return m_gene[3];
}

bool gene::shouldBoost()
{
	return m_gene[4];
}

std::string gene::getAsString()
{
	std::string rString = "";
	for (int i = 0; i < 5; i++)
	{
		rString += std::to_string(m_gene[i]);
	}
	return rString;
}
