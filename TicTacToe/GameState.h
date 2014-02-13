#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StateStack.h"
#include "GameBoard.h"
namespace mots{
class GameState: public State{
public:
	GameState(StateStack& stack, Context context);

	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);

private:
	void updateScore(mots::Tile::Owner winner);

	mots::GameBoard gameBoard;


};
}
#endif