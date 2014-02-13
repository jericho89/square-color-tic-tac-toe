//The Tile class represents one of the nine empty spaces in a game of Tic-Tac-Toe. It is composed
//of a drawable sf::RectangleShape and some metadata about who owns the Tile and what is its color/animation state.
//A Tile is supposed to animate smoothly between colors. 

#ifndef TILE_H
#define TILE_H
#include "SFML\Graphics.hpp"
#include <string>

namespace mots{

	//SFML's Color class represents a color with Red, Green, Blue, and Alpha.
	static const sf::Color tileGrey = sf::Color(222, 217, 219, 255);
	static const sf::Color playerGreen = sf::Color(50, 255, 50, 220);
	static const sf::Color playerGreenWin = sf::Color(0, 255, 0, 255);
	static const sf::Color enemyRed = sf::Color(255, 50, 50, 220);
	static const sf::Color enemyRedWin = sf::Color(255, 0, 0, 255);
	static const sf::Color nobodyWinGrey = sf::Color(120, 120, 120, 255);
	class Tile {

		public:
		static const enum Owner {Player, Computer, Nobody};
		//Constructor: the parameter is the Tile's true color -- when the board is reset, it will have this color again.
		Tile(sf::Color baseColor);

		//2nd constructor: variable size!
		Tile(sf::Color baseColor, sf::Vector2f size);


		
		void setTargetColor(sf::Color targetColor);
		//A Tile is always trying to match its targetColor. Every time updateColor() is called by the main game loop,
		//the actual color of the sf::RectangleShape is set a little closer to the target.
		bool updateColor();

		void setPosition(float x, float y);	
		void setOwner(Owner newOwner);

		Owner getOwner();
		sf::Vector2f getPosition();

		//contains() returns whether the Tile covers a given point on the screen.
		bool contains(int x, int y);

		//getTileFace() returns a const reference to the drawable sf::Rectangle, so it can be drawn in the RenderWindow -- but not modified.
		const sf::RectangleShape& getTileFace();

		sf::Color getCurrentColor();
		sf::Color getTargetColor();

		private:
		sf::Color originalColor;
		sf::Color targetColor;
		Owner owner;

	protected:
		sf::RectangleShape tileFace;
		

	};
};

#endif