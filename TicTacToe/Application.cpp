#include "Application.h"
#include "GameState.h"


namespace mots{
	Application::Application():window(sf::VideoMode(800, 600), "TicTacToe", sf::Style::Default),
	stateStack(State::Context(window, scores[0]))
{
	scores[0] = 0;
	scores[1] = 0;
	scores[2] = 0;
	registerStates();
	stateStack.pushState(States::ID::Game);
};

void Application::registerStates(){
	stateStack.registerState<GameState>(States::Game);

};

void Application::run(){

	//SFML's Clock class measures the elapsed time since the object was initialized or reset.
	sf::Clock clock;
	clock.restart();
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time fixedTimeStep = sf::seconds((1.0f / 30.0f));
	while (window.isOpen()){
		//Handle user input:
		processEvents();
		
		//Update the game board at a fixed rate:
		timeSinceLastUpdate = clock.getElapsedTime();
		accumulator += timeSinceLastUpdate;
		while (accumulator > fixedTimeStep){
			accumulator -= fixedTimeStep;
			update(fixedTimeStep);
			clock.restart();

		}

		draw();
		if (stateStack.isEmpty()) window.close();
	}
};



void Application::update(sf::Time dt){
	stateStack.update(dt);
};

void Application::draw(){
	window.clear(sf::Color::White);
	stateStack.draw();
};
void Application::processEvents(){
	sf::Event event;
	while (window.pollEvent(event)){

		stateStack.handleEvent(event);


	}
};
}