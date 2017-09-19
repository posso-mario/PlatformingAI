#include "stdafx.h"
#include "player.h"
#include "entry.h"
#include "gamemaster.h"
#include <iostream>

sf::Texture texture;
player::player()
{

}

player::~player()
{

}

void player::update(float elapsedTime)
{
	std::cout << "update called\n";
	sf::Sprite &masterSprite = visibleobj::getSprite();
	switch (currentAction)
	{
	case(run):
	{
		std::cout << "running\n";
		masterSprite.setTexture((*it_run));
		it_run++;
		if (it_run == _runList.end()) it_run = _runList.begin();
		
		break;
	}
	case(jump):
	{
		masterSprite.setTexture((*it_jump));
		it_jump++;
		if (it_jump == _jumpList.end()) it_jump = _jumpList.begin();
		break;
	}
	case(duck):
	{
		masterSprite.setTexture((*it_duck));
		it_duck++;
		if (it_duck == _duckList.end()) it_duck = _duckList.begin();
		break;
	}
	case(die):
	{
		masterSprite.setTexture((*it_die));
		it_die++;
		if (it_die == _dieList.end()) it_die = _dieList.begin();
		break;
	}
	}
	/***********************************************************/
	sf::Keyboard masterKeyboard = entry::getInput();
	if (masterKeyboard.isKeyPressed(sf::Keyboard::Space))
	{
		currentAction = jump;
	}
	else if (masterKeyboard.isKeyPressed(sf::Keyboard::Down))
	{
		currentAction = duck;
	}
	else
	{
		currentAction = run;
	}
	/***********************************************************/
	bool collision = gamemaster::getStatus();
	if (collision)
	{
		currentAction = die;
	}
}

void player::load()
{
	std::string filename_base_run = "images/wolf_runframe";
	std::string filename_base_duck = "images/wolf_runframe";
	std::string filename_base_jump = "images/wolf_jumpframe";
	std::string filename_base_die = "images/wolf_runframe";
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
