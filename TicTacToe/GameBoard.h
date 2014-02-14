//The GameBoard holds the nine Tiles that make up the game of Tic-Tac-Toe. Since my concept was that the human player would play against the board itself,
//this class also has the functions necessary to calculate the computer's move.
//Tic-Tac-Toe is a simple and thoroughly solved game, so I did not implement a minmax-style algorithm for the AI. Instead, on each turn, the AI
//iterates through a flow-chart that leads it reliably to a draw or a win. I decided that randomization and board rotations for variety were outside the scope
//of this project.

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "Tile.h"
#include "SFML\Graphics.hpp"
#include <vector>

namespace mots {

	class GameBoard {
	public:
		std::vector<mots::Tile> nineTiles;
		//The SFML class RectangleShape represents a rectangle that can be drawn to the RenderWindow, with fill and border colors, etc.
		//The blackBorders form a grid over the game-board.
		std::vector<sf::RectangleShape> blackBorders;
		//These two rectangles mask the left and right sides of the screen.
		sf::RectangleShape windowDressingLeft;
		sf::RectangleShape windowDressingRight;

		//The doomsDayClock is used at the end of the game to ensure that the end-of-game animations have enough time to run.
		sf::Clock doomsDayClock;

		GameBoard();
		void makeComputerMove();
		bool isHumanTurn();

		//calculateGameOver() analyzes the board to see if the last move was a game-ending move and marks the winning row
		//with a darker color. Lightweight isGameOver() returns whether the game is over (i.e., whether we're between games),
		//but does nothing else -- I use this one in the main game loop.
		bool calculateGameOver();
		bool isGameOver();
		
		//showEndgameColors() sets all the tiles on the board to the color of the winning team. 
		void showEndgameColors(mots::Tile::Owner winner);
		void resetBoard();
		mots::Tile::Owner whoWon();

		void draw(sf::RenderWindow& window);
		void update(sf::Time dt);
		void handleEvent(const sf::Event& event);


	private:

		mots::Tile::Owner winner;
		bool gameOver;

		//My AI's decision-making functions often need to consider the board in terms of lanes of three Tiles. I represent these as vectors of pointers
		//to the Tiles themselves. There are columns, rows, and diagonals.
		std::vector<mots::Tile*> columnA;
		std::vector<mots::Tile*> columnB;
		std::vector<mots::Tile*> columnC;
		std::vector<mots::Tile*> rowA;
		std::vector<mots::Tile*> rowB;
		std::vector<mots::Tile*> rowC;
		std::vector<mots::Tile*> diagonalA;
		std::vector<mots::Tile*> diagonalB;

		std::vector<std::vector<mots::Tile*>*> allTheLanes;

		//These functions look at one of the above lanes and return how many Tiles in it are owned by the Player, the Computer, or Nobody.
		int numberOfComputerTiles(std::vector<mots::Tile*> lane);
		int numberOfUnclaimedTiles(std::vector<mots::Tile*> lane);
		int numberOfPlayerTiles(std::vector<mots::Tile*> lane);

		//These private functions are called in the public function makeComputerMove(), and represent the meat of the decision-making.
		bool tryWin();
		bool tryBlock();
		bool tryFork();
		bool tryBlockFork();
		bool tryFancyBlockFork();
		bool tryTakeCenter();
		bool tryTakeOppositeCorner();
		bool tryTakeEmptyCorner();
		bool tryTakeEmptySide();


		

		
	
	};

};



#endif