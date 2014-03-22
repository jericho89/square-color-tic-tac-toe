#ifndef APPLICATION_H
#define APPLICATION_H
#include "StateStack.h"
namespace mots{
class Application{
public:
	Application();
	void run();

private:
	void registerStates();


	
	void update(sf::Time dt);
	void draw();
	void processEvents();

	void takeScreenshot();



sf::RenderWindow window;
mots::StateStack stateStack;
int scores [3];
};

}
#endif