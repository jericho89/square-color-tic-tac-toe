
//The Game object runs the game loop, and has private functions for the business of processing events, updating the game state, 
//and drawing it to the window (sfml::RenderWindow). It owns, and is initialized with, the game's window and the GameBoard itself.

#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "GameBoard.h"

#include "SFML\Graphics.hpp"



namespace mots {

	class Game {
	public:
		Game();
		//run() executes the game loop, taking care to update the game's state in fixed time-steps.
		void run();

	private:
		//These functions are used inside run().
		//processEvents() handles user input. 
		void processEvents();
		//update() steps all the Tiles through their animations.
		void update();
		//render() clears the window, draws the components of the game to the window, and tells the window to display the new frame.
		void render();

		//SFML's RenderWindow class provides an OS window that serves as a target for 2D drawing.
		mots::GameBoard gameBoard;
	};


}





#endif