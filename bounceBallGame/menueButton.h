#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#define X 0
#define Y 1

using namespace std;

int hoverButton(sf::Vector2f*, int[][2], int[]);
void setBP(sf::Sprite[], int[][2], int);

int hoverButton(sf::Vector2f *m, int buttonP[][2], int buttonS[])
{
	if (m->x > 900 - buttonS[X] && m->x < 900)
	{
		if (m->y > buttonP[0][Y] && m->y < (buttonS[Y] + buttonP[0][Y]))
			return 0;
		else if (m->y > buttonP[1][Y] && m->y < (buttonS[Y] + buttonP[1][Y]))
			return 1;
		else if (m->y > buttonP[2][Y] && m->y < (buttonS[Y] + buttonP[2][Y]))
			return 2;
		else if (m->y > buttonP[3][Y] && m->y < (buttonS[Y] + buttonP[3][Y]))
			return 3;
	}
	return 5;
}

void setBP(sf::Sprite sp[], int p[][2], int n)
{
	for (int i = 0; i < n; i++)
	{
		sp[i].setPosition(sf::Vector2f(p[i][X], p[i][Y]));
	}
}
