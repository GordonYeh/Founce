#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>

#define X 0
#define Y 1

using namespace std;

bool generateBlocks(int block_num, sf::RectangleShape blocks[], int block_size[], int block_pos[][2])
{

	sf::Texture block_texture;

	if (!block_texture.loadFromFile("block.png"))
		return FALSE;

	for (int i = 0; i < block_num; i++)
	{
		blocks[i].setSize(sf::Vector2f(block_size[X], block_size[Y]));
		blocks[i].setPosition(sf::Vector2f(block_pos[i][X], block_pos[i][Y]));
		blocks[i].setTexture(&block_texture);
		blocks[i].setFillColor(sf::Color(244,211,30));
		blocks[i].setOutlineThickness(block_size[Y] / 20);
		blocks[i].setOutlineColor(sf::Color(255, 255, 255));
		
	}

	return TRUE;
}

void setBlockPosition(int block_num, int block_size[], int block_pos[][2], int initial_pos[], int block_limit[])
{
	int x_gap = block_size[X] + 20;
	int y_gap = block_size[Y] + 10;
	int position[2] = { initial_pos[X], initial_pos[Y] };
	int count = 0;
	for (int i = 0; i < block_num; i++)
	{
		block_pos[i][X] = position[X];
		block_pos[i][Y] = position[Y];
		count++;
		position[X] += x_gap;
		
		if (count == block_limit[X])
		{
			position[Y] += y_gap;
			position[X] = initial_pos[X];
			count = 0;
		}
	}

}

void setBlocks(int block_num, int block_state[])
{
	for (int i = 0; i < block_num; i++)
	{
		block_state[i] = 1;
	}
}