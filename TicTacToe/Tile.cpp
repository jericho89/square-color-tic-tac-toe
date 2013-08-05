#include "Tile.h"
#include <SFML\Audio.hpp>

//a Tile controls one of the 9 squares on the game board
//and is implemented in terms of an sf::RectangleShape

//constructor: choose base color and sounds; Owner defaults to Nobody, color defaults to black
mots::Tile::Tile(sf::Color baseColor)
{
	//set default member values
	owner = Nobody;
	originalColor = baseColor;
	targetColor = originalColor;


	//initialize the tileFace
	tileFace = sf::RectangleShape(sf::Vector2f(200.00, 200.00));
	//the tileFace will have no border, and start at its originalColor
	tileFace.setOutlineThickness(0.0);
	tileFace.setFillColor(originalColor);

	
	
};

//color manipulation

void mots::Tile::setTargetColor(sf::Color targetColor)
{
	this->targetColor = targetColor;
	//I don't think I need to control this too closely -- any sf::Color ought to be valid
}

bool mots::Tile::updateColor()
{
	sf::Color currentColor = tileFace.getFillColor();
	if (currentColor == targetColor) return true;
	//build an intermediate color that is slightly closer to the target color:

	sf::Color intermediateColor = currentColor;
		//if an element of the color isn't there yet, push it 1 point towards the target
	if (intermediateColor.r != targetColor.r) intermediateColor.r = (intermediateColor.r + (intermediateColor.r < targetColor.r ? 1 : -1));
	if (intermediateColor.g != targetColor.g) intermediateColor.g = (intermediateColor.g + (intermediateColor.g < targetColor.g ? 1 : -1));
	if (intermediateColor.b != targetColor.b) intermediateColor.b = (intermediateColor.b + (intermediateColor.b < targetColor.b ? 1 : -1));
	if (intermediateColor.a != targetColor.a) intermediateColor.a = (intermediateColor.a + (intermediateColor.a < targetColor.a ? 1 : -1));

	//make the tileFace the intermediate color
	tileFace.setFillColor(intermediateColor);

	//return true if this update reached the target color
	if (tileFace.getFillColor() == targetColor) 
		return true;
	else
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
sf::RectangleShape mots::Tile::getTileFace()
{
	return tileFace;
};

bool mots::Tile::contains(float x, float y){
	sf::FloatRect boundary = tileFace.getGlobalBounds();
	return (boundary.contains(x, y));

}

sf::Color mots::Tile::getTargetColor(){return targetColor;};
