#include "TitleState.h"
#include "StateIdentifiers.h"
#include <stdexcept>

namespace mots{

	TitleState::TitleState(StateStack& stack, Context context){
		this->stack = &stack;
		this->context = context;

		if (!titleTexture.loadFromFile("titleImage.png")) throw new std::runtime_error("Image not found");
		titleSprite.setTexture(titleTexture);
		titleSprite.setPosition(sf::Vector2f(0.0, 0.0));

	};

	void TitleState::draw(){
		context.window->draw(titleSprite);

	}

	bool TitleState::update(sf::Time dt) {
		return false; //don't let lower states (shoudln't be any) get time
	}

	bool TitleState::handleEvent(const sf::Event& event) {
		switch (event.type){
		case sf::Event::Closed:
			context.window->close();
			break;
		
		case sf::Event::MouseButtonPressed:
			requestStackPop();
			requestStackPush(States::ID::Game);


		}

		return false;
	}





}