
#include <vector>
#include <iostream>
#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "GameBoard.h"
#include "SFML\System\Clock.hpp"



int main()
{
	//find out how big to make the window
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	//make the main window for the game
	sf::RenderWindow window(sf::VideoMode(800, 600, desktopSize.bitsPerPixel), "TicTacToe", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

//initialize the GameBoard, which holds both Tiles and sf::RectangleShape borders
	mots::GameBoard gameBoard;

//make the black rectangle for the screen vertical border
		sf::RectangleShape windowDressing = sf::RectangleShape(sf::Vector2f(100.0, 600.0));
		windowDressing.setOutlineThickness(0.0);
		windowDressing.setFillColor(sf::Color::Black);

	//run the program as long as the window is open
	while (window.isOpen())
	{
		//check all events triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			//"close requested" event -- close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			//left click in the window during the player's turn
			if ((event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Button::Left)) && gameBoard.isHumanTurn())
			{
				
				//if the left click was on an unclaimed tile, make it green
				for(int i=0; i < 9; i++)
				{
					if ((gameBoard.nineTiles[i].contains((event.mouseButton.x), event.mouseButton.y)) && (gameBoard.nineTiles[i].getOwner() == mots::Tile::Owner::Nobody))
					{
						gameBoard.nineTiles[i].setOwner(mots::Tile::Owner::Player);
						if (gameBoard.isGameOver())
						{
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
						else gameBoard.makeComputerMove();

						if (gameBoard.isGameOver())
						{
							gameBoard.showEndgameColors(gameBoard.whoWon());
							gameBoard.doomsDayClock = sf::Clock();
						}
					}
				}
			}

		// end event check
		}

		if (gameBoard.isGameOver()) 
		{
			if (gameBoard.doomsDayClock.getElapsedTime().asSeconds() >= 5){gameBoard.resetBoard();}
		}

		//clear the window with White color
		window.clear(sf::Color::White);

		//DRAW STUFF:
		
		//always draw black bars to the left and right, so the window looks 600 x 600
		windowDressing.setPosition(0.0, 0.0);
		window.draw(windowDressing);
		windowDressing.setPosition(700.0, 0.0);
		window.draw(windowDressing);

		//update the tile colors -- separate from the next loop to play with timing?

		for(int i=0; i<9; i++)
		{
			gameBoard.nineTiles[i].updateColor();

			
		}
		//draw the game board
		for(int i=0; i<9; i++)
		{
			window.draw(gameBoard.nineTiles[i].getTileFace());
		}

		//and the borders over it
		for(int i=0; i < 4; i++)
		{
			window.draw(gameBoard.blackBorders[i]);
		}


	
		//display what we drew
		window.display();

	}

	//TODO: delete everything just in case?
	return 0;
}