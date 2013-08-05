#include "GameBoard.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <algorithm>

mots::GameBoard::GameBoard(){
	//build the game board vector and initialize all 9 tiles

	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));

	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));

	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));

    //set the position of each tile
	//first row
	nineTiles[0].setPosition(100.0, 0.0);
	nineTiles[1].setPosition(300.0, 0.0);
	nineTiles[2].setPosition(500.0, 0.0);
	//second row
	nineTiles[3].setPosition(100.0, 200.0);
	nineTiles[4].setPosition(300.0, 200.0);
	nineTiles[5].setPosition(500.0, 200.0);
	//third row
	nineTiles[6].setPosition(100.0, 400.0);
	nineTiles[7].setPosition(300.0, 400.0);
	nineTiles[8].setPosition(500.0, 400.0);

//make the tile borders: an array of sf::RectangleShapes
	//vertical
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(20.0, 600.0)));
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(20.0, 600.0)));
	//horizontal
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(600.0, 20.0)));
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(600.0, 20.0)));
//color the borders black with no outline
	for (int i=0; i < 4; i++) {blackBorders[i].setFillColor(sf::Color(0 ,0 ,0, 255)); blackBorders[i].setOutlineThickness(0.0);}
//position the borders
	blackBorders[0].setPosition(290.0, 0.0);
	blackBorders[1].setPosition(490.0, 0.0);

	blackBorders[2].setPosition(100.0, 190.0);
	blackBorders[3].setPosition(100.0, 390.0);

//the player moves first:
	humanTurn = true;
//initialize winner
	winner = mots::Tile::Owner::Nobody;

//make the analysis vectors
		 columnA.push_back(&(nineTiles[0]));
		 columnA.push_back(&(nineTiles[3]));
		 columnA.push_back(&(nineTiles[6]));

		 columnB.push_back(&(nineTiles[1]));
		 columnB.push_back(&(nineTiles[4]));
		 columnB.push_back(&(nineTiles[7]));

		 columnC.push_back(&(nineTiles[2]));
		 columnC.push_back(&(nineTiles[5]));
		 columnC.push_back(&(nineTiles[8]));

		 rowA.push_back(&(nineTiles[0]));
		 rowA.push_back(&(nineTiles[1]));
		 rowA.push_back(&(nineTiles[2]));

		 rowB.push_back(&(nineTiles[3]));
		 rowB.push_back(&(nineTiles[4]));
		 rowB.push_back(&(nineTiles[5]));

		 rowC.push_back(&(nineTiles[6]));
		 rowC.push_back(&(nineTiles[7]));
		 rowC.push_back(&(nineTiles[8]));

		 diagonalA.push_back(&(nineTiles[0]));
		 diagonalA.push_back(&(nineTiles[4]));
		 diagonalA.push_back(&(nineTiles[8]));

		 diagonalB.push_back(&(nineTiles[2]));
		 diagonalB.push_back(&(nineTiles[4]));
		 diagonalB.push_back(&(nineTiles[6]));

		 //put these lanes in a list
		 allTheLanes.push_back(&(columnA));
		 allTheLanes.push_back(&(columnB));
		 allTheLanes.push_back(&(columnC));

		 allTheLanes.push_back(&(rowA));
		 allTheLanes.push_back(&(rowB));
		 allTheLanes.push_back(&(rowC));

		 allTheLanes.push_back(&(diagonalA));
		 allTheLanes.push_back(&(diagonalB));



};

bool mots::GameBoard::isHumanTurn()
{
	return humanTurn;
};

bool mots::GameBoard::isGameOver()
{
	//if the player got 3 in a row
	//for each each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);
		//does the player have 3 tiles in the current lane?
		if ((numberOfPlayerTiles(*currentLane) == 3)){
			//if so, set winner to Player and return true
			winner = mots::Tile::Owner::Player;
			//make the winning squares darker
			for (int j = 0; j < 3; j++){
				((allTheLanes[i])->at(j))->setTargetColor(playerGreenWin);
			}
			return true;
		}
	}

	//if the computer got 3 in a row
		//set winner to Computer
		//return true

	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);
		//does the Computer have 3 tiles in the current lane?
		if ((numberOfComputerTiles(*currentLane) == 3)){
			//if so, set winner to Player and return true
			winner = mots::Tile::Owner::Computer;
			for (int j = 0; j < 3; j++){
				((allTheLanes[i])->at(j))->setTargetColor(enemyRedWin);
			}
			return true;
		}
	}

	//else if all 9 squares are owned
		//set winner to Nobody
		//return true
	int allCount=0;
	for (int i=0; i < 8; i ++){
		if (nineTiles[i].getOwner() != mots::Tile::Owner::Nobody) allCount++;
	}
	if (allCount >=8){
		winner = mots::Tile::Owner::Nobody;
		return true;
	}


	//else return false
	return false;

};

void mots::GameBoard::makeComputerMove()
{
	//analyze the board and pick a Tile



	//win: do you have 2 in a row? is there a Nobody space in that row? pick it
	if (tryWin()) return;
	//block: does the player have 2 in a row? is there a Nobody space in that row? pick it
	if (tryBlock()) return;
	
	//fork: if two of your marked rows intersect, and they do not contain a Player cell, pick the tile at the intersection

	//block opponent's fork: if two enemy rows intersect, and they are not blocked, pick a tile next to one of your cells & in an un-blocked row
	//block fork 2: look for where an enemy would fork(????), and take that tile

	//center: if center not taken, take it
	if (tryTakeCenter()) return;
	//opposite corner: if opponent has a corner, take the opposite corner
	if (tryTakeOppositeCorner()) return;

	//empty corner: pick an empty corner
	if(tryTakeEmptyCorner()) return;

	//empty side: pick an empty side
	if(tryTakeEmptySide()) return;


	//make it the player's turn again
	humanTurn = true;
};

void mots::GameBoard::showEndgameColors(mots::Tile::Owner winner)
{
	//the player can't click anything until the board resets in GameBoard::resetBoard()
	humanTurn = false;
	//if winner = Player, set all Tiles targetColor to green
	for (int i=0; i < 9; i++){
		if (winner == mots::Tile::Owner::Player){
			if (nineTiles[i].getTargetColor() != mots::playerGreenWin) nineTiles[i].setTargetColor(mots::playerGreen);
		}
		//if winner = Computer, set all Tiles targetColor to red
		else if (winner == mots::Tile::Owner::Computer){
			if (nineTiles[i].getTargetColor() != mots::enemyRedWin) nineTiles[i].setTargetColor(mots::enemyRed);
		}
	}


	//if winner = Nobody, do nothing -- the board will be reset soon
};

void mots::GameBoard::resetBoard()
{
	//and Owner back to Nobody, which automatically resets the color
	//set all other Tile values back to default

	for (int i = 0; i < 9; i++){
		nineTiles[i].setOwner(mots::Tile::Owner::Nobody);

	}

	//set all GameBoard member values back to default
	winner = mots::Tile::Owner::Nobody;

	//and let the player click again
	humanTurn = true;
};

void mots::GameBoard::setHumanTurn(bool isHumanTurn){(this->humanTurn) = isHumanTurn;};

mots::Tile::Owner mots::GameBoard::whoWon(){return winner;};

bool mots::GameBoard::tryWin(){
//win: do you have 2 in a row? is there a Nobody space in that row? pick it
	//in each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);

		//in the lane we're looking at, could we win this turn?
		if ((numberOfComputerTiles(*currentLane) == 2) && (numberOfUnclaimedTiles(*currentLane) != 0)){
			//find and claim the empty space
			for (int j = 0; j < 3; j++){
				if (((allTheLanes[i])->at(j))->getOwner() == mots::Tile::Owner::Nobody){
					((allTheLanes[i])->at(j))->setOwner(mots::Tile::Owner::Computer);
					return true;
				}
			}
		}
	}
	//if you didn't find anything, return false
	return false;
};

bool mots::GameBoard::tryBlock(){
//block: does the player have 2 in a row? is there a Nobody space in that row? pick it
	//in each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);

		//could the player win next turn?
		if ((numberOfPlayerTiles(*currentLane) == 2) && (numberOfUnclaimedTiles(*currentLane) != 0)){
			//find and claim the empty space
			for (int j = 0; j < 3; j++){
				if (((allTheLanes[i])->at(j))->getOwner() == mots::Tile::Owner::Nobody){
					((allTheLanes[i])->at(j))->setOwner(mots::Tile::Owner::Computer);
					return true;
				}
			}
		}
	}
	//if you didn't find anything, return false
	return false;
};

bool mots::GameBoard::tryTakeCenter(){
//center: if center not taken, take it
	if ((nineTiles[4].getOwner()) == mots::Tile::Owner::Nobody){
		nineTiles[4].setOwner(mots::Tile::Owner::Computer);
		return true;
	}
	return false;
};

bool mots::GameBoard::tryTakeEmptyCorner(){

	//try the top left corner
		if (nineTiles[0].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[0].setOwner(mots::Tile::Owner::Computer);
			return true;
		}
	//try the top right corner
		if (nineTiles[2].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[2].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//try the bottom left corner
		if (nineTiles[6].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[6].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//try the bottom right corner
		if (nineTiles[8].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[8].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

		

return false;
};

bool mots::GameBoard::tryTakeEmptySide(){
	//this could be an iterator using i = 1; i<8; i+=2;
	//try the top side
		if (nineTiles[1].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[1].setOwner(mots::Tile::Owner::Computer);
			return true;
		}
	//try the right side
		if (nineTiles[5].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[5].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//try the bottom side
		if (nineTiles[7].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[7].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//try the left side
		if (nineTiles[3].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[3].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

return false;
};

bool mots::GameBoard::tryTakeOppositeCorner(){
//opposite corner: if Player has a corner, take the opposite corner

	//0 <---> 8

	if ((nineTiles[0].getOwner() == mots::Tile::Owner::Player) && (nineTiles[8].getOwner() == mots::Tile::Owner::Nobody)){
		nineTiles[8].setOwner(mots::Tile::Owner::Computer);
		return true;
	}
	if ((nineTiles[8].getOwner() == mots::Tile::Owner::Player) && (nineTiles[0].getOwner() == mots::Tile::Owner::Nobody)){
		nineTiles[0].setOwner(mots::Tile::Owner::Computer);
		return true;
	}

	//2 <--> 6
	if ((nineTiles[2].getOwner() == mots::Tile::Owner::Player) && (nineTiles[6].getOwner() == mots::Tile::Owner::Nobody)){
		nineTiles[6].setOwner(mots::Tile::Owner::Computer);
		return true;
	}
	if ((nineTiles[6].getOwner() == mots::Tile::Owner::Player) && (nineTiles[2].getOwner() == mots::Tile::Owner::Nobody)){
		nineTiles[2].setOwner(mots::Tile::Owner::Computer);
		return true;
	}
	return false;

};
// these functions look at a lane of 3 Tiles and return how many are owned by Computer, Player, or Nobody
int mots::GameBoard::numberOfComputerTiles(std::vector<mots::Tile*> lane){
	int counter = 0;
	for (int i = 0; i < 3; i++){
		if (lane[i]->getOwner() == mots::Tile::Owner::Computer){
			counter++;
		}
	}
	return counter;
};

int mots::GameBoard::numberOfPlayerTiles(std::vector<mots::Tile*> lane)
{
	int counter = 0;
	for (int i = 0; i < 3; i++){
		if (lane[i]->getOwner() == mots::Tile::Owner::Player){
			counter++;
		}
	}
	return counter;
};

int mots::GameBoard::numberOfUnclaimedTiles(std::vector<mots::Tile*> lane){
	int counter = 0;
	for (int i = 0; i < 3; i++){
		if (lane[i]->getOwner() == mots::Tile::Owner::Nobody){
			counter++;
		}
	}
	return counter;
};