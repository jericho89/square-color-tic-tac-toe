#include "GameBoard.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <random>


mots::GameBoard::GameBoard(){
	//Build the game board vector and initialize all 9 Tiles:

	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));

	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));

	nineTiles.push_back(mots::Tile(mots::tileGrey));
	nineTiles.push_back(mots::Tile(sf::Color::White));
	nineTiles.push_back(mots::Tile(mots::tileGrey));

    //Set the position of each tile
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

//Make the tile borders: an array of sf::RectangleShapes:
	//vertical
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(20.0, 600.0)));
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(20.0, 600.0)));
	//horizontal
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(600.0, 20.0)));
	blackBorders.push_back(sf::RectangleShape(sf::Vector2f(600.0, 20.0)));
//Color these borders black with no outline:
	for (int i=0; i < 4; i++) {blackBorders[i].setFillColor(sf::Color(0 ,0 ,0, 255)); blackBorders[i].setOutlineThickness(0.0);}
//Position the borders:
	blackBorders[0].setPosition(290.0, 0.0);
	blackBorders[1].setPosition(490.0, 0.0);

	blackBorders[2].setPosition(100.0, 190.0);
	blackBorders[3].setPosition(100.0, 390.0);

//Initialize the black rectangles that mask the left and right sides of the screen:
	windowDressingLeft = sf::RectangleShape(sf::Vector2f(100.0, 600.0));
	windowDressingLeft.setOutlineThickness(0.0);
	windowDressingLeft.setFillColor(sf::Color::Black);
	windowDressingLeft.setPosition(sf::Vector2f(0.0, 0.0));

	windowDressingRight = sf::RectangleShape(sf::Vector2f(100.0, 600.0));
	windowDressingRight.setOutlineThickness(0.0);
	windowDressingRight.setFillColor(sf::Color::Black);
	windowDressingRight.setPosition(sf::Vector2f(700.0, 0.0));

//Set default values for winner and gameOver:
	gameOver = false;
	winner = mots::Tile::Owner::Nobody;

//Construct the analysis vectors, as explained in GameBoard.h:
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
	//If the tiles are still changing colors, the human player can't make another move.
	for (mots::Tile i : nineTiles){
		if (i.getCurrentColor() != i.getTargetColor()) return false;
	}

	//If none of the tiles are still changing, then the human player can make a move.
	return true;

};


//calculateGameOver() analyzes the board to see if the last move was a game-ending move and marks the winning row
//with a darker color.
bool mots::GameBoard::calculateGameOver()
{
//If the Player got 3 in a row:
	//for each each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);
		//does the player have 3 tiles in the current lane?
		if ((numberOfPlayerTiles(*currentLane) == 3)){
			//if so, set winner to Player, mark the winning lane with a darker color, and return true:
			winner = mots::Tile::Owner::Player;
			for (int j = 0; j < 3; j++){
				((currentLane)->at(j))->setTargetColor(playerGreenWin);
			}
			gameOver = true;
			return gameOver;
		}
	}

//If the Computer got 3 in a row:
	//for each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);
		//does the Computer have 3 tiles in the current lane?
		if ((numberOfComputerTiles(*currentLane) == 3)){
			//if so, set winner to Computer, mark the winning lane with a darker color, and return true.
			winner = mots::Tile::Owner::Computer;
			for (int j = 0; j < 3; j++){
				((allTheLanes[i])->at(j))->setTargetColor(enemyRedWin);
			}
			gameOver = true;
			return gameOver;
		}
	}


//If nobody's won, but all 9 squares are owned, call a draw.

	int allCount=0;
	for (int i=0; i < 9; i ++){
		if (nineTiles[i].getOwner() != mots::Tile::Owner::Nobody) allCount++;
	}
	if (allCount >=9){
		winner = mots::Tile::Owner::Nobody;
		gameOver = true;
		return gameOver;
	}


//Otherwise (if nobody's won, and not all squares are owned), the game isn't over yet!
	gameOver = false;
	return gameOver;

};


//Lightweight isGameOver() returns whether the game is over (i.e., whether we're between games),
//but does nothing else -- I use this one in the main game loop.
bool mots::GameBoard::isGameOver()
{
	return gameOver;
};

void mots::GameBoard::makeComputerMove()
{
	//This is where the AI analyzes the board and picks a Tile.
	//To make its choice, it works through a simple flow-chart. If a high-priority move is not available, it moves on to
	//a less appealing move. This strategy is based on the summary of Tic-Tac-Toe strategy found at http://en.wikipedia.org/wiki/Tic-tac-toe#Strategy.


	//Win: Do you have 2 in a row? Is there an empty space in that row? Pick it.
	if (tryWin()) return;

	//Block: Does the player have 2 in a row? Is there an empty space in that row? Pick it.
	if (tryBlock()) return;
	

	//Try to create a "fork" -- a situation where we have two opportunities to win, and the human can only block one.
	if (tryFork()) return;
	//Block opponent's fork: foil the obvious three-corners fork by picking the Tile in the un-blocked Row or Column.
	if (tryBlockFork()) return;

	if (tryTakeCenter()) return;
	//Opposite corner: if the human has a corner, take the opposite corner.
	if (tryTakeOppositeCorner()) return;

	if(tryTakeEmptyCorner()) return;
	if(tryTakeEmptySide()) return;



};


//showEndgameColors() sets all the Tiles on the board to the color of the winning team.
void mots::GameBoard::showEndgameColors(mots::Tile::Owner winner)
{
	for (int i=0; i < 9; i++){
		if (winner == mots::Tile::Owner::Player){
			if (nineTiles[i].getTargetColor() != mots::playerGreenWin) nineTiles[i].setTargetColor(mots::playerGreen);
		}

		else if (winner == mots::Tile::Owner::Computer){
			if (nineTiles[i].getTargetColor() != mots::enemyRedWin) nineTiles[i].setTargetColor(mots::enemyRed);
		}
		else if (winner == mots::Tile::Owner::Nobody){
			nineTiles[i].setTargetColor(mots::nobodyWinGrey);
		}
	}


	
};


void mots::GameBoard::resetBoard()
{

	for (int i = 0; i < 9; i++){
		nineTiles[i].setOwner(mots::Tile::Owner::Nobody);

	}

	winner = mots::Tile::Owner::Nobody;
	gameOver = false;


};


mots::Tile::Owner mots::GameBoard::whoWon(){return winner;};

bool mots::GameBoard::tryWin(){
//Win: Do you have 2 in a row? Is there an empty space in that row? Pick it.


	//In each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);

		//in the lane we're looking at, could we win on this turn?
		if ((numberOfComputerTiles(*currentLane) == 2) && (numberOfUnclaimedTiles(*currentLane) != 0)){
			//If so, find and claim the empty space:
			for (int j = 0; j < 3; j++){
				if (((allTheLanes[i])->at(j))->getOwner() == mots::Tile::Owner::Nobody){
					((allTheLanes[i])->at(j))->setOwner(mots::Tile::Owner::Computer);
					return true;
				}
			}
		}
	}
	//If you didn't find anything, return false.
	return false;
};

bool mots::GameBoard::tryBlock(){
//Block: Does the player have 2 in a row? Is there an empty space in that row? Pick it.
	//In each lane,
	for (int i = 0; i < 8; i ++){
		std::vector<mots::Tile*> * currentLane = (allTheLanes[i]);

		//could the player win next turn?
		if ((numberOfPlayerTiles(*currentLane) == 2) && (numberOfUnclaimedTiles(*currentLane) != 0)){
			//If so, find and claim the empty space:
			for (int j = 0; j < 3; j++){
				if (((allTheLanes[i])->at(j))->getOwner() == mots::Tile::Owner::Nobody){
					((allTheLanes[i])->at(j))->setOwner(mots::Tile::Owner::Computer);
					return true;
				}
			}
		}
	}
	//If you didn't find anything, return false.
	return false;
};

bool mots::GameBoard::tryFork(){
//Try to create a "fork" -- a situation where we have two opportunities to win, and the human can only block one.
//For each open Tile, consider the lanes it occupies. If 2 lanes are not marked by the Player AND already contain a Computer tile, take this Tile.
//This is definitely the hairiest and most logically questionable function in the program.

	for(mots::Tile currentTile : nineTiles){
	//This kind of for-each loop is valid in the version of C++ 11 used in Visual Studio Express 2012. 


		if (currentTile.getOwner() == mots::Tile::Owner::Nobody){			//Only consider unclaimed tiles.

			//Find the lanes of this tile and put them in a new vector for analysis:
			std::vector<std::vector<mots::Tile*>*> lanesOfThisTile;
			//For each lane on the board,
			//if that lane has a pointer to the thing pointed to by currentTile, add it to lanesOfThisTile for analysis.
			for(std::vector<mots::Tile*>* i : allTheLanes){

				for(int j = 0; j > 2; j++){
					if ( (i->at(j)) == &currentTile) lanesOfThisTile.push_back(i);
				}
			}

			//Next, see if 2 lanesOfThisTile contain Computer tiles and are open.
			int countOfViableLanes = 0;
			//In each lane, 
			for(std::vector<mots::Tile*>* k : lanesOfThisTile){
				//If the lane contains Computer tiles and does not contain Player tiles, count it as a viable lane for forking.
				if ((numberOfComputerTiles(*k) > 0) && (numberOfPlayerTiles(*k) == 0)){
				countOfViableLanes++;
				}
			}

			//If there are 2+ viable lanes, pick this Tile!
			if (countOfViableLanes >= 2){
				currentTile.setOwner(mots::Tile::Computer);
				return true;
			}
			//otherwise, go on to the next tile...
		}

	} //end tile loop...
	//if no forking tile was found, return false
	return false;
};

bool mots::GameBoard::tryBlockFork(){
	//Block opponent's fork: foil the obvious three-corners fork by picking the Tile in the un-blocked Row or Column.
	//If the human already has 2 corners, try to take an unblocked side:
	int countPlayerCorners = 0;
	if (nineTiles[0].getOwner() == mots::Tile::Player) countPlayerCorners++;
	if (nineTiles[2].getOwner() == mots::Tile::Player) countPlayerCorners++;
	if (nineTiles[6].getOwner() == mots::Tile::Player) countPlayerCorners++;
	if (nineTiles[8].getOwner() == mots::Tile::Player) countPlayerCorners++;

	if (countPlayerCorners == 2){
		if (tryTakeEmptySide()) return true;
	}
	return false;
};

bool mots::GameBoard::tryTakeCenter(){
	if ((nineTiles[4].getOwner()) == mots::Tile::Owner::Nobody){
		nineTiles[4].setOwner(mots::Tile::Owner::Computer);
		return true;
	}
	return false;
};

bool mots::GameBoard::tryTakeRandomSequence(int i, int j, int k, int l){
	
	int accessOrder[4] = {i, j, k, l};
	std::random_shuffle(std::begin(accessOrder), std::end(accessOrder));





	//Try the first tile.
		if (nineTiles[accessOrder[0]].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[accessOrder[0]].setOwner(mots::Tile::Owner::Computer);
			return true;
		}
	//Try the second tile.
		if (nineTiles[accessOrder[1]].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[accessOrder[1]].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//Try the third tile.
		if (nineTiles[accessOrder[2]].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[accessOrder[2]].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

	//Try the fourth tile.
		if (nineTiles[accessOrder[3]].getOwner() == mots::Tile::Owner::Nobody){
			nineTiles[accessOrder[3]].setOwner(mots::Tile::Owner::Computer);
			return true;
		}

		

return false;
};

bool mots::GameBoard::tryTakeEmptyCorner(){
	return tryTakeRandomSequence(0, 2, 6, 8);

};

bool mots::GameBoard::tryTakeEmptySide(){
	int accessOrder[] = {1, 3, 5, 7};
	return tryTakeRandomSequence(1, 3, 5, 7);
	
};

bool mots::GameBoard::tryTakeOppositeCorner(){
//Opposite corner: if the Player has a corner, take the opposite corner.

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
// These functions look at a lane of 3 Tiles and return how many are owned by Computer, Player, or Nobody.
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

void mots::GameBoard::draw(sf::RenderWindow& window){

	//Draw the vertical screen borders:
		window.draw(windowDressingLeft);
		window.draw(windowDressingRight);

		//Draw the game board:
		for(int i=0; i<9; i++){
			window.draw(nineTiles[i].getTileFace());
		}

		//and the borders over it:
		for(int i=0; i < 4; i++){
			window.draw(blackBorders[i]);
		}

};

void mots::GameBoard::update(sf::Time dt){

	if (isGameOver()){
		if (doomsDayClock.getElapsedTime().asSeconds() >= 5){resetBoard();}
	}

	for(int i=0; i<9; i++){
		nineTiles[i].updateColor();			
	}

};

void mots::GameBoard::handleEvent(const sf::Event& event){
	//Left click in the window during the player's turn:
	if ((event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Button::Left)) && isHumanTurn()){

		//If the left click was on an unclaimed tile, make it green:
		for(int i=0; i < 9; i++){
			if ((nineTiles[i].contains((event.mouseButton.x), event.mouseButton.y)) && (nineTiles[i].getOwner() == mots::Tile::Owner::Nobody)){
				nineTiles[i].setOwner(mots::Tile::Owner::Player);
				if (calculateGameOver()){
					showEndgameColors(whoWon());
					doomsDayClock = sf::Clock();
				}
				else makeComputerMove();

				if (calculateGameOver()){
					showEndgameColors(whoWon());
					doomsDayClock = sf::Clock();
				}
			}
		}
	}
};