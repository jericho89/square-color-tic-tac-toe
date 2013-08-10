#include "Tile.h"
#include "GameBoard.h"
#include "Game.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include "SFML\System\Clock.hpp"

mots::Game::Game(): window(sf::VideoMode(800, 600), "TicTacToe", sf::Style::Fullscreen){
	//window.setFramerateLimit(60);
//initialize the GameBoard, which holds both Tiles and sf::RectangleShape borders
	mots::GameBoard gameBoard;
};

void mots::Game::run(){
	sf::Clock clock;
	clock.restart();
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time fixedTimeStep = sf::seconds((1.0f / 30.0f));
	while (window.isOpen()){
		//handle user input
		processEvents();
		
		//update the game board at a fixed rate
		//the main loop 'produces' time & the update function 'consumes' it in discrete chunks
		//should produce a steady 30 frames per second
		timeSinceLastUpdate = clock.getElapsedTime();
		accumulator += timeSinceLastUpdate;
		while (accumulator > fixedTimeStep){
			accumulator -= fixedTimeStep;
			update(fixedTimeStep);
			clock.restart();

		}

		render();

	}

};

void mots::Game::processEvents(){
	sf::Event event;
		while (window.pollEvent(event)){
			//"close requested" event -- close the window
			if (event.type == sf::Event::Closed){
				window.close();
			}

			//left click in the window during the player's turn
			if ((event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Button::Left)) && gameBoard.isHumanTurn()){
				
				//if the left click was on an unclaimed tile, make it green
				for(int i=0; i < 9; i++){
					if ((gameBoard.nineTiles[i].contains((event.mouseButton.x), event.mouseButton.y)) && (gameBoard.nineTiles[i].getOwner() == mots::Tile::Owner::Nobody)){
						gameBoard.nineTiles[i].setOwner(mots::Tile::Owner::Player);
						if (gameBoard.isGameOver()){
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
						else gameBoard.makeComputerMove();

						if (gameBoard.isGameOver()){
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
					}
				}
			}
		}// end event check

};

void mots::Game::update(sf::Time deltaTime){
		if (gameBoard.isGameOver()){
			if (gameBoard.doomsDayClock.getElapsedTime().asSeconds() >= 5){gameBoard.resetBoard();}
		}

		
		for(int i=0; i<9; i++){
			gameBoard.nineTiles[i].updateColor();			
		}
};

void mots::Game::render(){
		//clear the window with White color
		window.clear(sf::Color::White);

		//and the vertical screen borders
		window.draw(gameBoard.windowDressingLeft);
		window.draw(gameBoard.windowDressingRight);

		//draw the game board
		for(int i=0; i<9; i++){
			window.draw(gameBoard.nineTiles[i].getTileFace());
		}

		//and the borders over it
		for(int i=0; i < 4; i++){
			window.draw(gameBoard.blackBorders[i]);
		}



		window.display();
};