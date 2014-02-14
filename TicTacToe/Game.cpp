//The Game object runs the game loop, and has private functions for the business of processing events, updating the game state, 
//and drawing it to the window (sfml::RenderWindow). It owns, and is initialized with, the game's window and the GameBoard itself.

#include "Tile.h"
#include "GameBoard.h"
#include "Game.h"

#include <vector>

#include "SFML\Graphics.hpp"
#include "SFML\System\Clock.hpp"

mots::Game::Game(){
};


//run() contains the game loop, which runs as long as the window is open.
//I use a standard strategy to make the game update in fixed time-steps: the game loop 'produces' time & the update() function 'consumes' it in discrete chunks.
void mots::Game::run(){
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
			update();
			clock.restart();

		}

		//Draw the game board to the window:
		render();

	}

};

//processEvents handles user input. SFML's RenderWindow class maintains a queue of sfml::Events, which include mouse clicks, key-presses,
//and OS-standard requests to close the window. We iterate through our window's queue and respond to left-clicks and close-window requests.
void mots::Game::processEvents(){
	sf::Event event;
		while (window.pollEvent(event)){
			//"Close requested" event -- close the window.
			if (event.type == sf::Event::Closed){
				window.close();
			}

			//Left click in the window during the player's turn:
			if ((event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Button::Left)) && gameBoard.isHumanTurn()){
				
				//If the left click was on an unclaimed tile, make it green:
				for(int i=0; i < 9; i++){
					if ((gameBoard.nineTiles[i].contains((event.mouseButton.x), event.mouseButton.y)) && (gameBoard.nineTiles[i].getOwner() == mots::Tile::Owner::Nobody)){
						gameBoard.nineTiles[i].setOwner(mots::Tile::Owner::Player);
						if (gameBoard.calculateGameOver()){
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
						else gameBoard.makeComputerMove();

						if (gameBoard.calculateGameOver()){
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
					}
				}
			}
		}// end event check

};

void mots::Game::update(){

	
	if (gameBoard.isGameOver()){
		if (gameBoard.doomsDayClock.getElapsedTime().asSeconds() >= 5){gameBoard.resetBoard();}
	}
		
		for(int i=0; i<9; i++){
			gameBoard.nineTiles[i].updateColor();			
		}
};

void mots::Game::render(){
		//clear the window with White color:
		window.clear(sf::Color::White);

		//Draw the vertical screen borders:
		window.draw(gameBoard.windowDressingLeft);
		window.draw(gameBoard.windowDressingRight);

		//Draw the game board:
		for(int i=0; i<9; i++){
			window.draw(gameBoard.nineTiles[i].getTileFace());
		}

		//and the borders over it:
		for(int i=0; i < 4; i++){
			window.draw(gameBoard.blackBorders[i]);
		}


		//Finally, push what we've drawn to the window.
		window.display();
};