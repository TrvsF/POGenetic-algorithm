#include "levels.h"

levels* levels::s_instance = NULL;

levels* levels::INSTANCE()
{
	if (s_instance == NULL)
		s_instance = new levels();

	return s_instance;
}

void levels::loadDefaultLevel()
{
	resetLevel();

	m_goal = new goal(Vector2(220, 110));

	// set where goal should be
	m_currentLevelObjects.push_back(m_goal);

	// add player camera object
	m_currentLevelObjects.push_back(new player(Vector2(400, 300)));

	loadLevel("debuglevel.pog");

	agent_manager::INSTANCE()->startDebugTest();
}

bool levels::loadLevel(std::string fileName)
{
	e_currentReadType currentType;

	std::ifstream file(fileName);

	if (file.is_open())
	{
		std::string builder[2];
		std::string currentWord;

		int wordCount = 0;

		currentType = idle;

		while (file >> currentWord)
		{
			// printf("%s\n", currentWord.c_str());
			switch (currentType)
			{
			case idle:
				wordCount = 0;
				builder[wordCount] = currentWord;
				if (builder[wordCount] == "NAME")
				{
					currentType = name;
				}
				if (builder[wordCount] == "TYPE")
				{
					currentType = type;
				}
				if (builder[wordCount] == "WALL")
				{
					currentType = brick;
				}
				if (builder[wordCount] == "PLAYER")
				{
					currentType = character;
				}
				break;
			case name:
				m_levelName = currentWord;
				currentType = idle;
				break;
			case type:
				m_currentLevelType = custom;
				currentType = idle;
				break;
			case brick:
				if (wordCount == 0)
				{
					wordCount++;
					builder[wordCount] = currentWord;
				}
				else
				{
					int x = std::stoi(builder[wordCount]);
					int y = std::stoi(currentWord);
					m_currentLevelObjects.push_back(new wall(Vector2((float)x, (float)y)));
					currentType = idle;
				}
				break;
			case character:
				if (wordCount == 0)
				{
					wordCount++;
					builder[wordCount] = currentWord;
				}
				else
				{
					int x = std::stoi(builder[wordCount]);
					int y = std::stoi(currentWord);

					for (int i = 0; i < agent_manager::INSTANCE()->POPULATION_MULTIPLYER; i++)
					{
						agent* tempAgent = new agent(Vector2((float)x, (float)y), m_goal);
						m_currentLevelObjects.push_back(tempAgent);
						agent_manager::INSTANCE()->addAgent(tempAgent);
					}

					currentType = idle;
				}
				break;
			}
		}
		file.close();
	}
	return true;
}

levels::levels()
{
	loadDefaultLevel();
}

levels::~levels()
{
	
}

void levels::resetLevel()
{
	m_currentLevelType = menu;

	m_currentLevelObjects.clear();
	m_currentLevelTextures.clear();
}

void levels::update()
{
	
}

void levels::render()
{
	for (auto const& entity : m_currentLevelObjects)
	{
		entity->render();
	}
	for (auto const& texture : m_currentLevelTextures)
	{
		// TODO : make some sort of system to render in game textures that dont have a game object
	}
	agent_manager::INSTANCE()->getDebugData(debugMessages);
	for (int i = 0; i < DEBUG_LINES; i++)
	{
		m_dLines[i] = new texture("terminus.ttf", debugMessages[i].c_str(), 21, { 0, 0, 0 });
		m_dLines[i]->render(Vector2( (float) 900, (float) 20 + (i * 20) ), 0);
	}
}
