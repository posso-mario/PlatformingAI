#include "stdafx.h"
#include "player.h"
#include "entry.h"
#include "gamemaster.h"
#include <iostream>

bool holdAction = false;
int jumpState = 0;
int duckState = 1;
int dieState = 1;
int multiplier = 1;
int framerateDivider = 0;
int jumpHeight[60];

sf::Texture texture;
player::player()
{
	jumpHeight[0] = 0;
	jumpHeight[1] = -5;
	jumpHeight[2] = -15;
	for (int i = 3; i < 15; i++)
	{
		if (i < 9) jumpHeight[i] = -1;
		else jumpHeight[i] = 1;
	}
	jumpHeight[15] = 15;
	jumpHeight[16] = 5;
	jumpHeight[17] = 0;
	for (int i = 54; i < 60; i++)
	{
		jumpHeight[i] = 0;
	}
	holdAction = false;
	jumpState = 0;
	duckState = 1;
	dieState = 1;
	framerateDivider = 0;

}

player::~player()
{

}

void player::update(float elapsedTime)
{
	//std::cout << currentAction;
	sf::Sprite &masterSprite = visibleobj::getSprite();
	switch (currentAction)
	{
	case(run):
	{
		//std::cout << "running\n";
		if (framerateDivider == 0)
		{
			masterSprite.setTexture((*it_run));
			it_run++;
			if (it_run == _runList.end()) it_run = _runList.begin();
			framerateDivider = FRAME_RATE_DIVISION;
		}
		else
		{
			framerateDivider--;
		}
		
		
		break;
	}
	case(jump):
	{
		if (framerateDivider == 0)
		{
			masterSprite.setTexture((*it_jump));
			if (jumpState < 3) it_jump++;
			if (jumpState > 14) it_jump++;
			visibleobj::setPosition(visibleobj::getPosition().x, visibleobj::getPosition().y + 7*jumpHeight[jumpState]);
			jumpState++;
			if (it_jump == _jumpList.end()) { it_jump = _jumpList.begin(); holdAction = false; jumpState = 0; multiplier = 1; }
			framerateDivider = FRAME_RATE_DIVISION;

		}
		else
		{
			framerateDivider--;
		}
		break;
	}
	case(duck):
	{
		if (framerateDivider == 0)
		{
			masterSprite.setTexture((*it_duck));
			it_duck++;
			duckState += duckState;
			if (duckState < 5) it_duck++;
			if (duckState == 64) { duckState = -2; }
			if (it_duck == _duckList.end()) { it_duck = _duckList.begin(); holdAction = false; duckState = 1; }
			framerateDivider = FRAME_RATE_DIVISION;

		}
		else
		{
			framerateDivider--;
		}
		break;
	}
	case(die):
	{
		if (framerateDivider == 0)
		{
			masterSprite.setTexture((*it_die));
			visibleobj::setPosition(380, 668);
			it_die++;
			dieState += dieState;
			if (dieState < 5) it_die++;
			if (dieState == 32768) { dieState = -2; }
			if (it_die == _dieList.end()) { it_die = _dieList.begin(); holdAction = false; dieState = 1; entry::setDeath(); }
			framerateDivider = FRAME_RATE_DIVISION;

		}
		else
		{
			framerateDivider--;;
		}
		break;
	}
	}
	/***********************************************************/
	sf::Keyboard masterKeyboard = entry::getInput();
	if (!holdAction)
	{
		if (masterKeyboard.isKeyPressed(sf::Keyboard::Space))
		{
			currentAction = jump;
			holdAction = true;
		}
		else if (masterKeyboard.isKeyPressed(sf::Keyboard::Down))
		{
			currentAction = duck;
			holdAction = true;
		}
		else
		{
			currentAction = run;
			holdAction = false;
		}
	}
	/***********************************************************/
	bool collision = entry::getGM().checkCollision();
	if (collision)
	{
		currentAction = die;
		holdAction = true;
	}
}

void player::load()
{
	std::string filename_base_run = "images/wolf_runframe";
	std::string filename_base_duck = "images/wolf_duckframe";
	std::string filename_base_jump = "images/wolf_jumpframe";
	std::string filename_base_die = "images/wolf_dieframe";
	sf::Texture texture;
	for (int i = 0; i < 6; i++)
	{
		char c = '0' + i;
		std::string end = ".png";
		std::string filename_run = filename_base_run + c + end;
		std::string filename_duck = filename_base_duck + c + end;
		std::string filename_die = filename_base_die + c + end;
		std::string filename_jump = filename_base_jump + c + end;
		if (texture.loadFromFile(filename_run) != true)
			assert(false);
		player::_runList.push_back(texture);
		if (texture.loadFromFile(filename_jump) != true)
			assert(false);
		player::_jumpList.push_back(texture);
		if (texture.loadFromFile(filename_duck) != true)
			assert(false);
		player::_duckList.push_back(texture);
		if (texture.loadFromFile(filename_die) != true)
			assert(false);
		player::_dieList.push_back(texture);
	}
	it_run = _runList.begin();
	it_jump = _jumpList.begin();
	it_duck = _duckList.begin();
	it_die = _dieList.begin();
	visibleobj::load("images/wolf_runframe0.png");
}

player::playeraction player::getAction()
{
	return player::currentAction;
}
