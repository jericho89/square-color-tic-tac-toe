//This state machine is lifted from the tutorial book SFML Game Development by Moreira, Hansson, and Haller. Its purpose is to let the application transition between
//a TitleState, the main GameState, and an EndState.
#ifndef STATE_H
#define STATE_H
#include <memory>
#include "StateIdentifiers.h"
#include "SFML\Graphics.hpp"


namespace mots{

class StateStack;
class State{
	
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context{
		Context(sf::RenderWindow& window, int& scores);
		Context();
		(sf::RenderWindow*) window;
		//[0]green, [1] draw, [2] red
		int* scores;
	};

public:
	State(StateStack& stack, Context context);
	State();
	virtual ~State();

	//Each actual state must implement these functions itself.
	virtual void draw()=0;
	//If we return true to these functions, updates and events will be passed to lower states as well.
	virtual bool update(sf::Time dt)=0;
	virtual bool handleEvent(const sf::Event& event)=0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;


	(StateStack*) stack;
	Context context;
};
}
#endif