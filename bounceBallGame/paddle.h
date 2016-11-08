#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class paddle :
	public sf::RectangleShape
{
public:
	//Generates:
	// - starting poision paddle
	// - dimension of the paddle
	paddle(int x, int y);

	// Set the position of the paddle
	// P - the position vector
	// The paddle only moves in the x direction
	void move(sf::RectangleShape *shape, sf::Vector2f *P);

	void setDimen(sf::RectangleShape *shape);

	void getDimen(int d[]);

	// Check if there is a collision
	void checkStatus();

	//paddle dimension
	float length[2];

	//paddle position
	float pos[2];
	
private:
	//window dimension
	int winX, winY;
};

