#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "Tile.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>

namespace mots {

	class GameBoard {
	public:
		std::vector<mots::Tile> nineTiles;
		std::vector<sf::RectangleShape> blackBorders;
		GameBoard();
		void makeComputerMove();
		bool isHumanTurn();
		bool isGameOver();
		void showEndgameColors(mots::Tile::Owner winner);
		void resetBoard();
		void setHumanTurn(bool isHumanTurn);
		mots::Tile::Owner whoWon();
		sf::Clock doomsDayClock;


	private:
		bool humanTurn;
		mots::Tile::Owner winner;

		std::vector<mots::Tile*> columnA;
		std::vector<mots::Tile*> columnB;
		std::vector<mots::Tile*> columnC;
		std::vector<mots::Tile*> rowA;
		std::vector<mots::Tile*> rowB;
		std::vector<mots::Tile*> rowC;
		std::vector<mots::Tile*> diagonalA;
		std::vector<mots::Tile*> diagonalB;

		std::vector<std::vector<mots::Tile*>*> allTheLanes;

		int numberOfComputerTiles(std::vector<mots::Tile*> lane);
		int numberOfUnclaimedTiles(std::vector<mots::Tile*> lane);
		int numberOfPlayerTiles(std::vector<mots::Tile*> lane);

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