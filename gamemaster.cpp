#include "stdafx.h"
#include "gamemaster.h"
#pragma once
#include "stdafx.h"
#include "gamemaster.h"
#include "objmngr.h"

std::string obs_base = "obs";

int gamemaster::last_match = 0;
bool gamemaster::playerStatus = false;
visibleobj * gamemaster::player;
visibleobj * gamemaster::obstacle;


gamemaster::gamemaster()
{
}

gamemaster::~gamemaster()
{

}

bool gamemaster::getStatus()
{
	return playerStatus;
}

void gamemaster::advanceObstacle()
{
	for (int i = last_match + 1; i < last_match + 11; i++)
	{
		std::string number = std::to_string(i);
		std::string obstacle = obs_base + number;
		if ((gamemaster::obstacle = entry::getManager().get(obstacle)) != NULL)
		{
			last_match = i;
			return;
		}
	}
}