#pragma once
#include "visibleobj.h"
#include <list>

class player : public visibleobj
{
public:
	enum playeraction { run, duck, die, jump };

	int player_width = 230;
	int player_height = 100;

	player();

	~player();

	void update(float elapsedTime);

	void load();

	playeraction getAction();
	

private:
	std::list<sf::Texture> _runList, _jumpList, _dieList, _duckList;
	std::list<sf::Texture>::iterator it_run,it_jump,it_duck,it_die;
	playeraction currentAction;
	
};