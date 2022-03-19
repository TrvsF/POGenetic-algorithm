/*----------
	level manager class
	handles level loading and all game entities on given levels

	things a level needs to be loaded
	 - a level type
	 - 

	things a level can contain
	 - the next level

	a. travis ~24th dec
----------*/
#ifndef _LEVELS_H
#define _LEVELS_H

#include <SDL.h>
#include "player.h"
#include "wall.h"
#include "agent.h"
#include "agent_manager.h"
#include "goal.h"
#include <fstream>
#include <string>

class levels
{
	private:
		levels();
		~levels();

		enum e_levelType { menu, story, custom };

		enum e_currentReadType { name, type, brick, character, idle };

		static levels* s_instance;

		std::string m_levelName;

		e_levelType m_currentLevelType;

		std::list<game_entity*> m_currentLevelObjects;
		std::list<texture*> m_currentLevelTextures;

		void resetLevel();

		//------------------//
		// DEBUG OBJECTS
		std::list<wall*> m_walls;

		player* m_playerChar;

		const int DEBUG_LINES = 4;
		std::string debugMessages[4];
		texture* m_dLines[4];

		goal* m_goal;
		//------------------//

	public:
		static levels* INSTANCE();

		void loadDefaultLevel();
		bool loadLevel(std::string fileName);

		void update();
		void render();
};
#endif