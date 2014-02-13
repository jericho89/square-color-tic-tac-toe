/* 
Project: TicTacToe
Author: Josh Gross

This project is an implementation of Tic-Tac-Toe. It's meant to be distinguished by its clean and soothing aesthetic.
The human player competes against the game-board by taking turns claiming tiles. As tiles are claimed, they fade
smoothly to either green (for the human) or red (for the game-board). When the game ends, the board resets, and the game
can be played again. 

My goal for this project was to apply what I've taught myself about object-oriented programming and C++ in the
practical context of building a simple game. I focused on designing sensible classes with appropriate responsibilities
and tried to make my code easy to read and maintain.

In this project, the Game class handles the game loop. 
The GameBoard class is composed of nine colored Tiles and several black borders. It tracks the state of the game and 
makes moves in response to the human player.
The Tile class represents one of the nine spaces in a game of Tic-Tac-Toe. 

I make extensive use of classes from SFML (Simple and Fast Multimedia Library) 2.0, an open-source library meant for games
and multimedia projects. Its website is http://sfml-dev.org/ . I'll note and explain SFML classes and functions in my comments.



*/


#include "Application.h"



int main(){
	mots::Application application;
	application.run();

	return 0;
}