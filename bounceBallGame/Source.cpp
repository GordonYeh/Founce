
/* Game by : Gordon Yeh
* 
*/

/* GAME RULES (requires update)
*	Bounce the ball back with the paddle
*	If the ball touches the back wall you lose
*	
*
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <windows.h>

#include "paddle.h"
#include "ball.h"

#include "eventsHandling.h"
#include "menueButton.h"
#include "block.h"

#define X 0
#define Y 1

using namespace std;

bool checkReturn(ball *b, paddle *p);
void loadScoreDisplay(sf::Texture t[], sf::Sprite s[], int px, int py);
//check to see if curser is hovering over a button
void loadLifeDisplay(sf::Texture *t, sf::Sprite *s, int px, int py);
#ifdef guard
enum{ start, highscore, info, quit };
#endif
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//main function
int main()//int argc, char* argv[])
{
	
	//scoring display
	sf::Texture num[10];
	sf::Sprite scoring1[10];
	sf::Sprite scoring10[10];
	loadScoreDisplay(num, scoring1, 47, 0);
	loadScoreDisplay(num, scoring10, 0, 0);
	int tenth = 0;
	int oneth = 0;

	//dimensions of the window
	const int winX = 900;
	const int winY = 900;
	sf::RenderWindow window(sf::VideoMode(winX, winY), "Founce");
	window.setFramerateLimit(70);

	//menue button
	int menueBD[2] = { 700, 100 }; //button dimensions
	int menueBP[4][2] = { { 200, 200 }, { 200, 350 }, { 200, 500 }, { 200, 650 } }; //button positions
	sf::Texture menueBT[4]; //button textures (on)
	sf::Texture menueBOff; //button texture (off)
	sf::Sprite menueBSp[4];
	if (!menueBT[start].loadFromFile("startButtonOn.png"))
		cout << "error: loading button image" << endl;
	for (int i = 0; i < 4; i++)
	{
		menueBSp[i].setTexture(menueBT[start]);
	}
	setBP(menueBSp, menueBP, 4);
	
	//life bar
	const int lifeLim = 3;
	const int lifeRad = 52/2;
	int lifeNum = 0;
	sf::Texture lifeText;
	if (!lifeText.loadFromFile("life.png"))
	{
		cout << "error: loading life bar display" << endl;
		system("pause");
	}

	sf::CircleShape lifeDisp[lifeLim];
	for (int i = 0; i < lifeLim; i++)
	{
		lifeDisp[i].setRadius(lifeRad);
		lifeDisp[i].setTexture(&lifeText);
		lifeDisp[i].setOrigin(sf::Vector2f(lifeRad, lifeRad));
		lifeDisp[i].setPosition(sf::Vector2f(winX - lifeRad*2.3*(2.5 - i), lifeRad));
	}


	/*game status:
	* 0 - off
	* 1 - on
	*/
	int gameStatus = 0;
	int state = 0;

	//generate the paddle
	paddle pad1(winX, winY);
	sf::RectangleShape padS1 = pad1;
	pad1.setDimen(&padS1);

	//dimension of the paddle
	int d[2];
	pad1.getDimen(d);
	int pPosY = pad1.pos[Y];

	//blocks 5x7
	/*  
	* Block Order
	* [0] [1] [2] [3] [4]
	* [5] [6] [7] [8] [9]
	* ......
	*/
	int block_limit[2] = { 7, 9 };
	int block_size[2] = { 100, 50 };
	int initial_pos[2] = { (winX - block_limit[X] * block_size[X]) / 2, (winY - block_limit[Y] * block_size[Y]) / 3};
	const int block_num = 5 * 7; 
	int block_position[block_num][2];
	setBlockPosition(block_num, block_size, block_position, initial_pos, block_limit);
	int block_stat[block_num]; //0 dead, 1 alive
	//generate blocks into a matrix
	sf::RectangleShape blocks[block_num];
	if (!generateBlocks(block_num, blocks, block_size, block_position))
	{
		cout << "error in generating blocks" << endl;
		system("pause");
	}

	//test block
	/*
	sf::RectangleShape test_block;
	sf::Texture test_texture;
	test_texture.loadFromFile("block1.png");
	test_block.setSize(sf::Vector2f(block_size[X], block_size[Y]));
	test_block.setPosition(sf::Vector2f(initial_pos[X], initial_pos[Y]));
	test_block.setTexture(&test_texture);
	*/

	//generate the ball
	ball* ball1;
	sf::CircleShape* ballS1;
	sf::Vector2f mouseP;
	int resetPoint;

	sf::Event event;

	while (window.isOpen())
	{
		//get mouse position
		mouseP = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

			//if curser is over the start button increase the size
			if (gameStatus == 0)
			{
				int state = hoverButton(&mouseP, menueBP, menueBD);
				if (handleEvents(&event, &window, menueBSp, menueBP, state, &gameStatus)) return 0;
			}

			if (gameStatus == 1)
			{
				ball1 = new ball(d, winX, winY);
				ballS1 = ball1;
				ball1->setDimen(ballS1);
				resetPoint = pad1.pos[Y] - d[Y] / 2 - ball1->r;
			}

			//game loop
			while (gameStatus == 1){

				//check to see if the window is closed
				sf::Event event;
				if (windowClosed(&event, &window)) return 0;

				//aquire mouse position - the paddle follows it
				mouseP = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

				//set paddle to the current mouse position
				pad1.move(&padS1, &mouseP);

				if (checkReturn(ball1, &pad1) && ball1->getVy() > 0)
				{
					//increase the return 
					ball1->returned();
					ball1->setYPos(resetPoint);
					ball1->reverseY();
					ball1->changeState(ballS1);
					oneth = ball1->returns % 10;
					tenth = ball1->returns / 10;				
				}

				ball1->move(ballS1);

				//life bar display
				if (ball1->life == lifeLim)
				{
					gameStatus = 0;
				}
				
				//set ball to the next position
				window.clear(sf::Color(183, 168, 129));
				for (int i = ball1->life; i < lifeLim; i++) window.draw(lifeDisp[i]);
				
				//window.draw(test_block);
				//display scoring
				//oneth place
				window.draw(scoring1[oneth]);
				//tenth place
				window.draw(scoring10[tenth]);
				window.draw(padS1);
				window.draw(*ballS1);
				window.display();

			}
			window.clear(sf::Color(255, 225, 220));
			for (int i = 0; i < 4; i++)
			{
				window.draw(menueBSp[i]);
			}
			window.display();
	}
	return 0;
}


bool checkReturn(ball *b, paddle *p)
{
	// check if the ball contacts the paddle in Y
	if (b->pos[X] > (p->pos[X] - p->length[X]/2) && b->pos[X] < (p->pos[X] + p->length[X]/2))
	{
		//check in X now
		if ((b->pos[Y] + b->r) > (p->pos[Y] - p->length[Y]/2) && (b->pos[Y] + b->r) < (p->pos[Y] + p->length[Y]/2))
		{
			int delta = b->pos[X] - p->pos[X];
			b->setVx(2 / p->length[X]*delta);
			return TRUE;
		}
	} 
	return FALSE;
}

void loadScoreDisplay(sf::Texture t[], sf::Sprite s[], int px, int py)
{
	if (!t[0].loadFromFile("0.png"))
		cout << "error in loading images" << endl;
	if (!t[1].loadFromFile("1.png"))
		cout << "error in loading images" << endl;
	if (!t[2].loadFromFile("2.png"))
		cout << "error in loading images" << endl;
	if (!t[3].loadFromFile("3.png"))
		cout << "error in loading images" << endl;
	if (!t[4].loadFromFile("4.png"))
		cout << "error in loading images" << endl;
	if (!t[5].loadFromFile("5.png"))
		cout << "error in loading images" << endl;
	if (!t[6].loadFromFile("6.png"))
		cout << "error in loading images" << endl;
	if (!t[7].loadFromFile("7.png"))
		cout << "error in loading images" << endl;
	if (!t[8].loadFromFile("8.png"))
		cout << "error in loading images" << endl;
	if (!t[9].loadFromFile("9.png"))
		cout << "error in loading images" << endl;

	for (int i = 0; i < 10; i++)
	{
		s[i].setTexture(t[i]);
		s[i].setPosition(px, py);
	}

}

// state: 1 - good,  0 - bad
void loadLifeDisplay(sf::Texture *t, sf::Sprite *s, int px, int py, int state)
{
	if (state)
	{
		if (!t->loadFromFile("lifeGood.png"))
			cout << "error: loading life bar display" << endl;
	}
	else {
		if (!t->loadFromFile("lifeBad.png"))
			cout << "error: loading life bar display" << endl;
	}

	s->setTexture(*t);
	s->setPosition(sf::Vector2f(px, py));
}

