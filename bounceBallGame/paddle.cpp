#include "paddle.h"
#include <iostream>
#define X 0
#define Y 1
using namespace std;

paddle::paddle(int x, int y)
{
	length[X] = x / 6;
	length[Y] = y / 100;
	pos[Y] = y - y / 15;
	winX = x - length[X]/2;
	winY = y;
}


void paddle::move(sf::RectangleShape *shape, sf::Vector2f *P){

	//check if the mouse is off screen
	//set limit so paddle stays within the window
	if (P->x > winX){
		pos[X] = winX;
	}
	else if (P->x < length[X] / 2){
		pos[X] = length[X]/ 2;
	}
	else{
		pos[X] = P->x;
	}

	shape->setPosition(sf::Vector2f(pos[X], pos[Y]));
}


void paddle::setDimen(sf::RectangleShape *shape){
	shape->setSize(sf::Vector2f(length[X], length[Y]));
	shape->setOrigin(sf::Vector2f(length[X] / 2, length[Y]/ 2));
}

void paddle::getDimen(int d[]){
	d[0] = length[X];
	d[1] = length[Y];
}