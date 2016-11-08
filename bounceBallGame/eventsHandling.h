#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "menueButton.h"

#define X 0
#define Y 1

using namespace std;

bool windowClosed(sf::Event*, sf::RenderWindow*);
bool mousePressed(sf::Event*, sf::RenderWindow*);
bool handleEvents(sf::Event*, sf::RenderWindow*, sf::Sprite[], int[][2], int, int*);
bool pauseEvent();

enum{ start, highscore, info, quit };

bool windowClosed(sf::Event *e, sf::RenderWindow *w)
{
	while (w->pollEvent(*e))
	{
		if (e->type == sf::Event::Closed)
		{
			w->close();
			return TRUE;
		}
	}
	return FALSE;
}

bool mousePressed(sf::Event *e, sf::RenderWindow *w)
{
	while (w->pollEvent(*e))
	{
		if (e->type == sf::Event::MouseButtonPressed)
		{
			return TRUE;
		}
	}
	return FALSE;
}

bool handleEvents(sf::Event *e, sf::RenderWindow *w, sf::Sprite sp[], int pos[][2], int stat, int *gamestat)
{
	switch (stat)
	{
	case start:
		sp[start].setPosition(sf::Vector2f(pos[start][X] - 100, pos[start][Y]));
		if (mousePressed(e, w))
		{
			cout << "game starts!" << endl;
			*gamestat = 1;
		}
		return FALSE;
	case highscore:
		sp[highscore].setPosition(sf::Vector2f(pos[highscore][X] - 100, pos[highscore][Y]));
		//cout << "highscore" << endl;
		return FALSE;
	case info:
		sp[info].setPosition(sf::Vector2f(pos[info][X] - 100, pos[info][Y]));
		//cout << "info" << endl;
		return FALSE;
	case quit:
		sp[quit].setPosition(sf::Vector2f(pos[quit][X] - 100, pos[quit][Y]));
		//cout << "quit" << endl;
		return FALSE;
	default:
		//cout << "nothing" << endl;
		setBP(sp, pos, 4);
		if (windowClosed(e, w)) return TRUE;
		else return FALSE;
	}
}
