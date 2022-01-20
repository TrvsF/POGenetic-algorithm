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
	for (int i = 0; i < sizeof(m_gene); i++)
	{
		m_gene[i] = randomBinary();
	}
}

gene::~gene()
{
}
