#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.h"
#include <ctime>
#include <math.h>
#include <Windows.h>

#define X  0
#define Y 1 

using namespace std;


ball::ball(int d[], int x, int y)
{
	r = d[0] / 6;
	lim[X] = x - r;
	lim[Y] = y - r;
	pos0[X] = x / 2;
	pos0[Y] = y / 2;
	returns = 0;
	angle = 0;
	textureTimer = 0;
	hitState = 0;
	life = 0;

	getVelo();
	//random generate a random uni-velocity
	srand(time(0));
	v[Y] =  (float)(rand() % 31)/100 + (float)0.4;
	v[X] =  sqrt(1 - pow(v[Y], 2))*pow(-1, rand() % 2);

	//load texture
	if (!ballTReg.loadFromFile("ballReg.png")  || !ballTHit.loadFromFile("ballHit.png"))
	{
		cout << "error: could not load ball texture" << endl;
		system("pause");
	}
}

void ball::setDimen(sf::CircleShape *s)
{
	s->setOrigin(sf::Vector2f(r,r));
	s->setRadius(r);
	s->setPosition(sf::Vector2f(pos0[X], pos0[Y]));
	s->setTexture(&ballTReg);
	t[X] = clock();
	t[Y] = clock();
}

void ball::move(sf::CircleShape *s)
{

	//calculate the next position
	pos[X] = pos0[X] + vm*v[X] * (float)(clock() - t[X]) / (float)CLOCKS_PER_SEC;
	pos[Y] = pos0[Y] + vm*v[Y] * (float)(clock() - t[Y]) / (float)CLOCKS_PER_SEC;
	
	//printf("Displacement: (%i, %i)\n", pos[X], pos[Y]);
	//printf("Velocity: (%.2f, %.2f)\n", v[X], vm*v[Y]);
	//Sleep(1000);
	
	s->setPosition(pos[X], pos[Y]);
	s->setRotation(angle);

	//check for collisions
	if (collisionCheckY() || collisionCheckX())
	{
		changeState(s);
	}

	//timer for the hit texture
	if (hitState == 1){
		textureTimer--;
		if (textureTimer == 0){
			hitState = 0;
			s->setTexture(&ballTReg);
		}
	}

	angle++;
}

/* change the magnitude of velocity
- depending on the # of returns achieved
- v = f(returns) = 750*sin(re*pi/200)+150
- range: 150 ~ 900 pixels/sec
*/
void ball::getVelo()
{
	
	vm = 1200 * sin((double)returns * 3.14 / 75.0) + 400;
}

/* check if the ball has hit a wall in the Y directon
locations:
- y = 0
- y = lim[Y]
*/
bool ball::collisionCheckY()
{
	if (pos[Y] > lim[Y]){
		reverseY();
		setYPos(lim[Y]);
		life++;
		return TRUE;
	}

	if (pos[Y] < r){
		reverseY();
		setYPos(r);
		return TRUE;
	}

	return FALSE;
}

/* check if the ball has hit a wall in the X directon
locations
- x = 0
- x = lim[X]
*/
bool ball::collisionCheckX()
{
	if (pos[X] > lim[X]){
		reverseX();
		setXPos(lim[X]);
		return TRUE;
	}

	if (pos[X] < r){
		reverseX();
		setXPos(r);
		return TRUE;
	}

	return FALSE;
}

//reverse the y velocity
void ball::reverseY()
{
	v[Y] = -v[Y];
	t[Y] = clock();
}

//reverse the x velocity
void ball::reverseX()
{
	v[X] = -v[X];
	t[X] = clock();
}

//increase the return score by 1
void ball::returned()
{
	returns++;
	getVelo();
	cout << returns << endl;
}

//set the y position to the parameter passed
void ball::setYPos(int pos)
{
	pos0[Y] = pos;
}

//set the x position to the parameter passed
void ball::setXPos(int pos)
{
	pos0[X] = pos;
}

void ball::setVx(float velo)
{
	v[X] = velo;
	resetX();
}

//reset x data for stability issues
void ball::resetX()
{
	pos0[X] = pos[X];
	t[X] = clock();
}

void ball::changeState(sf::CircleShape *s)
{
	hitState = 1;
	textureTimer = 30;
	s->setTexture(&ballTHit);
}

float ball::getVy()
{
	return v[Y];
}