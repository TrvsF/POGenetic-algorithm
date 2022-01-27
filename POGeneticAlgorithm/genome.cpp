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

void genome::populate()
{
	for (int i = 0; i < 2000; i++)
	{
		m_genome[i] = new gene();
	}
}
