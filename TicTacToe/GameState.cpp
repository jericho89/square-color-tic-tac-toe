#include "GameState.h"
namespace mots{
GameState::GameState(StateStack& stack, State::Context context){
	this->stack = &stack;
	this->context = context;

};


void GameState::draw(){
		gameBoard.draw(*context.window);
};

bool GameState::update(sf::Time dt){
		gameBoard.update(dt);
		return false; //no lower State will receive this update call
};

bool GameState::handleEvent(const sf::Event& event){

	switch (event.type){

	case sf::Event::Closed:
		context.window->close();
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left){
			gameBoard.handleEvent(event);
		}
	}

	return false; //no lower State will receive this event
};



}