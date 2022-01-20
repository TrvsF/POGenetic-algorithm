#include "genome.h"

genome::genome()
{
	populate();
}

genome::~genome()
{
}

void genome::populate()
{
	for (int i = 0; i < sizeof(m_genome); i++)
	{
		m_genome[i] = new gene();
	}
}
