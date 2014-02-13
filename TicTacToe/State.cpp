#include "State.h"
#include "StateStack.h"

namespace mots{
State::Context::Context(sf::RenderWindow& window, int& scores){
	(this->window) = &window;
	(this->scores) = &scores;
};
State::Context::Context(){
	window = nullptr;};

State::State(StateStack& stack, State::Context context){
	this->stack = &stack;
	this->context = context;
};
State::State(){this->stack = nullptr;};

State::~State(){};


void State::requestStackPush(States::ID stateID){
	stack->pushState(stateID);
};

void State::requestStackPop(){
	stack->popState();
};

void State::requestStateClear(){
	stack->clearStates();
};

State::Context State::getContext() const{
	return this->context;
};
}