#ifndef TILE_H
#define TILE_H
#include "SFML\Graphics.hpp"
#include <string>

namespace mots{
	static const sf::Color tileGrey = sf::Color(222, 217, 219, 255);
	static const sf::Color playerGreen = sf::Color(50, 255, 50, 220);
	static const sf::Color playerGreenWin = sf::Color(0, 255, 0, 255);
	static const sf::Color enemyRed = sf::Color(255, 50, 50, 220);
	static const sf::Color enemyRedWin = sf::Color(255, 0, 0, 255);
	class Tile {

		public:
		static const enum Owner {Player, Computer, Nobody};
		//constructor: choose baseColor -- the "true" color of the game board -- and the sounds associated with this space
			Tile(sf::Color baseColor);

		//functions to manage the color and transparency of sf::RectangleShape tileFace. Changes are gradual over the period time (seconds)
			// don't know how to do this yet, so I'm just wrapping setFillColor while I work on other things

			//current idea: the main loop uses setTargetColor once, then runs updateColor() on each Tile during the draw phase
			//updateColor +1s each element until it matches the targetColor, and returns true then
		void setTargetColor(sf::Color targetColor);
		bool updateColor();

		void setPosition(float x, float y);	
		void setOwner(Owner newOwner);

		Owner getOwner();
		sf::Vector2f getPosition();

		//ask if the Tile contains a given point
		bool contains(int x, int y);

		//return a copy of the drawable sf::Rectangle -- maybe this should be const by reference instead
		sf::RectangleShape getTileFace();
		//void playSound();

		sf::Color getTargetColor();

		private:
		sf::Color originalColor;
		sf::Color targetColor;
		Owner owner;
		sf::RectangleShape tileFace;
		

	};
};

#endif