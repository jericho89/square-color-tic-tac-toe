#include "GameState.h"
namespace mots{
GameState::GameState(StateStack& stack, State::Context context){
	this->stack = &stack;
	this->context = context;

};


void GameState::draw(){
		//clear the window with White color:
		context.window->clear(sf::Color::White);
		gameBoard.draw(*context.window);
};

bool GameState::update(sf::Time dt){
		gameBoard.update(dt);
		return false;
};

bool GameState::handleEvent(const sf::Event& event){

	if (event.type == sf::Event::Closed){
		context.window->close();
	}



	//Left click in the window during the player's turn:
	if ((event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Button::Left)) && gameBoard.isHumanTurn()){

		//If the left click was on an unclaimed tile, make it green:
		for(int i=0; i < 9; i++){
			if ((gameBoard.nineTiles[i].contains((event.mouseButton.x), event.mouseButton.y)) && (gameBoard.nineTiles[i].getOwner() == mots::Tile::Owner::Nobody)){
				gameBoard.nineTiles[i].setOwner(mots::Tile::Owner::Player);
				if (gameBoard.calculateGameOver()){
					gameBoard.showEndgameColors(gameBoard.whoWon());
					updateScore(gameBoard.whoWon());
					gameBoard.doomsDayClock = sf::Clock();
				}
				else gameBoard.makeComputerMove();

				if (gameBoard.calculateGameOver()){
					gameBoard.showEndgameColors(gameBoard.whoWon());
					updateScore(gameBoard.whoWon());
					gameBoard.doomsDayClock = sf::Clock();
				}
			}
		}
	}
	return false;
};

void GameState::updateScore(mots::Tile::Owner winner){
	//[0]green, [1] draw, [2] red
	switch(winner){
	case mots::Tile::Owner::Player:
		context.scores[0]++;
		break;
	case mots::Tile::Owner::Nobody:
			context.scores[1]++;
			break;
	case mots::Tile::Owner::Computer:
		context.scores[2]++;
	}


};


}