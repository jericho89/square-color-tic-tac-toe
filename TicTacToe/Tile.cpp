#include "Tile.h"
#include <SFML\Audio.hpp>



//Constructor: the parameter is the Tile's original color -- when the board is reset, it will have this color again
mots::Tile::Tile(sf::Color baseColor)
{
	owner = Nobody;
	originalColor = baseColor;
	targetColor = originalColor;

	//The tileFace is the drawable rectangle that represents the Tile on screen.
		//The SFML class Vector2f represents two-dimensional vectors in terms of floats. Here, it specifies the dimensions of the rectangle.
	tileFace = sf::RectangleShape(sf::Vector2f(200.00, 200.00));
	//The tileFace will have no border, and start at its originalColor.
	tileFace.setOutlineThickness(0.0);
	tileFace.setFillColor(originalColor);

	
	
};

mots::Tile::Tile(sf::Color baseColor, sf::Vector2f size){
	owner = Nobody;
	originalColor = baseColor;
	targetColor = originalColor;

	//The tileFace is the drawable rectangle that represents the Tile on screen.
		//The SFML class Vector2f represents two-dimensional vectors in terms of floats. Here, it specifies the dimensions of the rectangle.
	tileFace = sf::RectangleShape(size);
	//The tileFace will have no border, and start at its originalColor.
	tileFace.setOutlineThickness(0.0);
	tileFace.setFillColor(originalColor);

};


void mots::Tile::setBaseColor(sf::Color baseColor){
	this->originalColor = baseColor;
	targetColor = baseColor;
};

void mots::Tile::buildAnimation(){
	auto stepWithFloor = [] (int target, int current) {
		int step;
		if (target == current) return 0;

		step = (target-current)/NUMBER_FRAMES;
		if (step == 0) step = (target > current? 1 : -1);
		return step;

	};

	auto direction = [] (int step) {
		if (step >= 0) return true;
		else return false;
	};

	sf::Color currentColor = getCurrentColor();
	animation.r = stepWithFloor(targetColor.r, currentColor.r);
	animation.rDirection = direction(animation.r);

	animation.g = stepWithFloor(targetColor.g, currentColor.g);
	animation.gDirection = direction(animation.g);

	animation.b = stepWithFloor(targetColor.b, currentColor.b);
	animation.bDirection = direction(animation.b);

	animation.a = stepWithFloor(targetColor.a, currentColor.a);
	animation.aDirection = direction(animation.a);



};

void mots::Tile::setTargetColor(sf::Color targetColor)
{
	this->targetColor = targetColor;
	buildAnimation();
	frameCount = 0;

}


//updateColor() pushes the color of the Tile one step closer to its target. If the color is already on-target, or
//this update brings it on-target, it returns true.
/*bool mots::Tile::updateColor()
{
	sf::Color currentColor = tileFace.getFillColor();
	if (currentColor == targetColor) return true;

	//Build an intermediate color that is slightly closer to the target color:
	sf::Color intermediateColor = currentColor;
	//If an element of the intermediate color isn't there yet, push it 1 point towards the target:
	if (intermediateColor.r != targetColor.r) intermediateColor.r = (intermediateColor.r + (intermediateColor.r < targetColor.r ? 1 : -1));
	if (intermediateColor.g != targetColor.g) intermediateColor.g = (intermediateColor.g + (intermediateColor.g < targetColor.g ? 1 : -1));
	if (intermediateColor.b != targetColor.b) intermediateColor.b = (intermediateColor.b + (intermediateColor.b < targetColor.b ? 1 : -1));
	if (intermediateColor.a != targetColor.a) intermediateColor.a = (intermediateColor.a + (intermediateColor.a < targetColor.a ? 1 : -1));

	//Make the tileFace the intermediate color.
	tileFace.setFillColor(intermediateColor);

	//Return true if this update reached the target color; otherwise, return false.
	if (tileFace.getFillColor() == targetColor) 
		return true;
	else
		return false;

}; */


bool mots::Tile::updateColor(){

	//if it's already time to end the animation, abort!

	sf::Color currentColor = getCurrentColor();
	if (currentColor == targetColor) return true;


	//otherwise, animate...
	sf::Color intermediate;	
	auto smartStep = [] (int frame, bool direction, int target, int current) {
		//outputs the resultant value
		if (current == target) return target;
		if (direction && ((current + frame) > target)) return target;
		if ((!direction) && ((current + frame) < target)) return target;
		return (current + frame);
	};
	intermediate.r = smartStep(animation.r, animation.rDirection, targetColor.r, currentColor.r);
	intermediate.g = smartStep(animation.g, animation.gDirection, targetColor.g, currentColor.g);
	intermediate.b = smartStep(animation.b, animation.bDirection, targetColor.b, currentColor.b);
	intermediate.a = smartStep(animation.a, animation.aDirection, targetColor.a, currentColor.a);
	frameCount++;

	tileFace.setFillColor(intermediate);
	return false;


};

void mots::Tile::setPosition(float x, float y)
{
	tileFace.setPosition(x, y);
};	

void mots::Tile::setOwner(Owner newOwner)
{
	owner = newOwner;
	if (newOwner == mots::Tile::Owner::Computer) {
		setTargetColor(mots::enemyRed);
	}
	else if (newOwner == mots::Tile::Owner::Player){
		setTargetColor(mots::playerGreen);
	}
	else if (newOwner == mots::Tile::Owner::Nobody){
		setTargetColor(originalColor);
	}

};

mots::Tile::Owner mots::Tile::getOwner()
{
	return owner;
};

sf::Vector2f mots::Tile::getPosition()
{
	sf::Vector2f position = tileFace.getPosition();

 return position;
};
const sf::RectangleShape& mots::Tile::getTileFace()
{
	return tileFace;
};

//contains() returns whether the Tile covers a given point on the screen.
bool mots::Tile::contains(int x, int y){
	sf::FloatRect boundary = (tileFace.getGlobalBounds());
	return (boundary.contains(float(x), float(y)));

}

sf::Color mots::Tile::getTargetColor(){return targetColor;};

sf::Color mots::Tile::getCurrentColor(){return (tileFace.getFillColor());};