//This state machine is lifted from the tutorial book SFML Game Development by Moreira, Hansson, and Haller. Its purpose is to let the application transition between
//a TitleState, the main GameState, and a EndState.

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "StateStack.h"


namespace mots{


StateStack::StateStack(State::Context context): stack(), pendingList(), context(context), factories()
{};

StateStack::PendingChange::PendingChange(Action action, States::ID stateID){
	this->action = action;
	this->stateID = stateID;
};

StateStack::PendingChange::PendingChange(Action action){
	this->action = action;
};

void StateStack::handleEvent(const sf::Event& event){
	//the StateStack receives events and delivers them to active states

	

	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges(); //update the stack, too
};

void StateStack::update(sf::Time dt){
	
	for(auto itr = stack.rbegin(); itr !=stack.rend(); ++itr){
		if (!(*itr)->update(dt)) break; //give each active state the update order, but give up if a state says to by returning false
	}

	applyPendingChanges(); //update the stack, too
};

void StateStack::draw(){
	//order every state to draw itself, oldest first
	for (State::Ptr& itr : stack){
		(itr)->draw();
	}
	context.window->display();

};


void StateStack::pushState(States::ID stateID){
	pendingList.push_back(PendingChange(Action::Push, stateID));

};

void StateStack::popState(){
	pendingList.push_back(PendingChange(Action::Pop));
};

void StateStack::clearStates(){
	pendingList.push_back(PendingChange(Action::Clear));
};

bool StateStack::isEmpty() const{
	return stack.empty();
};


//createState uses the stored factory functions to produce the requested state.
State::Ptr StateStack::createState(States::ID stateID){
	auto func = factories[stateID];
	return func();
	
};

//execute all requested push/pop/clear requests; called only when safe
void StateStack::applyPendingChanges(){

	for(StateStack::PendingChange change : pendingList){

		switch (change.action){
		case Push:
			stack.push_back(createState(change.stateID));
			break;
		case Pop:
			stack.pop_back();
			break;
		case Clear:
			stack.clear();
			break;
		}
	}
	pendingList.clear();
};
}