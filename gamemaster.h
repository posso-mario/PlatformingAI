#pragma once
#include "stdafx.h"
#include "entry.h"

class gamemaster
{
public:
	gamemaster();
	~gamemaster();
	static bool getStatus();
	static void advanceObstacle();

private:
	static visibleobj * player;
	static visibleobj * obstacle;
	static bool playerStatus;
	static int last_match;
};