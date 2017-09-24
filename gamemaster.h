#pragma once
#include "stdafx.h"
//#include "entry.h"
#include "obstacle.h"
#include "player.h"

class gamemaster
{
public:
	gamemaster();
	~gamemaster();
	//static bool getStatus();
	//static void advanceObstacle();
	bool createObstacle();
	bool checkCollision();
	int getScore();
	void resetScore();
	void registerPlayer(player * _player);
	void deleteAll();

private:
	player * playerPtr;
	std::list<obstacle> _obstacles;
	bool playerStatus;
	int last_match;
	int _score;
};