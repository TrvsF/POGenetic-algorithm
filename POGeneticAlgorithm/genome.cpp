#include "genome.h"

genome::genome()
{
	
}

genome::~genome()
{
}

gene* genome::getGeneAtIndex(int i)
{
	if (m_genome == NULL)
	{
		return NULL;
	}
	return m_genome[i];
}

void genome::setGeneAtIndex(int i, gene* g)
{
	m_genome[i] = g;
}

void genome::deleteGenes()
{
	for (int i = 0; i < SIZE; i++)
	{
		delete m_genome[i];
	}
}

void genome::populate()
{
	for (int i = 0; i < SIZE; i++)
	{
		m_genome[i] = new gene();
	}
}
