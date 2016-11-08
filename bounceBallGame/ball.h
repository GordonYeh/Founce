#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ball :
	public sf::CircleShape
{
public:
	//d - dimension of paddle
	//x, y - dimension of window
	ball(int d[], int x, int y);

	//move to the next position
	//includes checking for collisions
	void move(sf::CircleShape *s);

	//sets the dimensions of the ball
	void setDimen(sf::CircleShape *s);
	
	bool collisionCheckY();
	bool collisionCheckX();
	void returned();

	//reverse the velocity in Y
	void reverseY();

	//reverse the velocity in X
	void reverseX();

	void setYPos(int pos);
	void setXPos(int pos);

	void setVx(float);

	//resets the x position for stability issures
	void resetX();

	void changeState(sf::CircleShape *s);

	float getVy();
	int returns;
	int pos[2];
	int r;
	int life;

private:
	void getVelo();
	int lim[2];
	
	//kinematics data
	
	int pos0[2];

	//magnitude of velocity
	float vm;
	float v[2];

	//timing
	float t[2];

	//texture
	sf::Texture ballTReg;
	sf::Texture ballTHit;

	int angle;
	int textureTimer;
	int hitState;
};

