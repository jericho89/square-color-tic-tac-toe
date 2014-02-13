//This state machine is lifted from the tutorial book SFML Game Development by Moreira, Hansson, and Haller. Its purpose is to let the application transition between
//a TitleState, the main GameState, and a EndState.

#ifndef STATESTACK_H
#define STATESTACK_H


#include "SFML/System.hpp"
#include <memory>
#include <functional>
#include "StateIdentifiers.h"
#include "State.h"

namespace mots{


class StateStack: private sf::NonCopyable{
	
public:
	enum Action{Push, Pop, Clear};
	struct PendingChange{
		PendingChange(Action action, States::ID stateID);
		PendingChange(Action action);
		Action action;
		States::ID stateID;
	};


public:
	explicit StateStack(mots::State::Context context); //constructor

	//registerState() matches a state with its factory function.
	template<typename T> void registerState(States::ID stateID){

		std::function<State::Ptr ()> factoryFunction = [this] (){
			std::unique_ptr<State> madeState(new T(*this, context));
			return madeState;
		};

		factories[stateID] = factoryFunction;
	};

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

private:
	std::vector<State::Ptr> stack;
	std::vector<PendingChange> pendingList;
	State::Context context;
	std::map<States::ID, std::function<State::Ptr()>> factories;

};




}
#endif