//the Game object breaks initialization, processing events, updating, and drawing out of the main() function, mainly for readability

#ifndef GAME_H
#define GAME_H
#include "Tile.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include "GameBoard.h"

namespace mots {

	class Game {
	public:
		Game();
		void run();

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();

		sf::RenderWindow window;
		mots::GameBoard gameBoard;
	};


}





#endif