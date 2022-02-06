#include "genome.h"

genome::genome()
{
	populate();
}

genome::~genome()
{
}

gene* genome::getGeneAtIndex(int i)
{
	return m_genome[i];
}

void genome::setGeneAtIndex(int i, gene* g)
{
	m_genome[i] = g;
}

void genome::populate()
{
	for (int i = 0; i < SIZE; i++)
	{
		m_genome[i] = new gene();
	}
}
