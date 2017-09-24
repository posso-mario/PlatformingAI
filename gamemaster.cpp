//#include "stdafx.h"
//#include "gamemaster.h"
#pragma once
#include "stdafx.h"
#include "gamemaster.h"
#include "objmngr.h"
#include "time.h"
#include "entry.h"


std::string obs_base = "obs";
int currentObsNum = 0;
obstacle * latest_obs = NULL;
obstacle * colliding_obs = NULL;
obstacle * last_scored_obs = NULL;

//int gamemaster::last_match = 0;
//bool gamemaster::playerStatus = false;
//std::list<obstacle> _obstacles;
//player * gamemaster::playerPtr;
int obj_count = 0;
int removed_count = 0;
int score;

void updateCollider(std::list<obstacle> & obstacles, int player_x);




gamemaster::gamemaster()
{
	_score = 0;
	score = 0;
}

gamemaster::~gamemaster()
{

}

int gamemaster::getScore()
{
	return _score;
}

void gamemaster::resetScore()

{
	_score = 0;
	score = 0;
}

bool allowCreate(obstacle * obs)
{
	//std::cout << obs << "\n";
	if ((1024 - obs->getPosition().x) > 500)
	{
		return true;
	}
	return false;
}

bool gamemaster::createObstacle()
{
	bool create = true;
	//std::cout << "obstacle list size: " << _obstacles.size() << "\n";
	if (latest_obs != NULL)
	{
		create = allowCreate(latest_obs);
	}
	//std::cout << create << "\n";
	if (create)
	{
		if ((rand() % 100) == 0)
		{
			obstacle * obs = new obstacle();
			obs->load(obstacle::obstacle_t::good);
			obs->setPosition(1064, 718);
			obs->setVelocity(-800);
			obs->setInstNum(obj_count);
			_obstacles.push_back(*obs);
			objmngr & Mngr = entry::getManager();
			std::string append = std::to_string(obj_count);
			std::list<obstacle>::iterator it = _obstacles.end();
			it--;
			Mngr.add(obs_base + append, &(*it));
			obj_count++;
			latest_obs = &(*it);
			//std::cout << "created good object" << time(NULL) << "\n";
			return true;
		}
		else if ((rand() % 100) == 0)
		{
			obstacle * obs = new obstacle();
			obs->load(obstacle::obstacle_t::bad);
			obs->setPosition(1064, 718);
			obs->setVelocity(-800);
			obs->setInstNum(obj_count);
			_obstacles.push_back(*obs);
			objmngr & Mngr = entry::getManager();
			std::string append = std::to_string(obj_count);
			std::list<obstacle>::iterator it = _obstacles.end();
			it--;
			Mngr.add(obs_base + append, &(*it));
			obj_count++;
			latest_obs = &(*it);
			//std::cout << "created bad object" << time(NULL) << "\n";
			return true;
		}
	}
	return false;
}
/*
bool gamemaster::getStatus()
{
	return playerStatus;
}*/
/*
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
}*/

void gamemaster::registerPlayer(player * _player)
{
	srand(time(NULL));
	playerPtr = _player;
	colliding_obs = NULL;
	last_scored_obs = NULL;
	latest_obs = NULL;
}

bool gamemaster::checkCollision()
{
	updateCollider(_obstacles, playerPtr->getPosition().x);
	_score = score;
	if (colliding_obs != NULL)
	{
		if ((*colliding_obs).getPosition().x <= (playerPtr->getPosition().x + playerPtr->player_width))
		{
			//std::cout << "removing something \n";
			if ((*colliding_obs).getPosition().y <= (playerPtr->getPosition().y + playerPtr->player_height))
			{
				int instNum = colliding_obs->getInstNum();
				std::string append = std::to_string(instNum);
				entry::getManager().remove(obs_base + append, true);
				std::list<obstacle>::iterator it = _obstacles.begin();
				while (it != _obstacles.end())
				{
					if ((*it).getInstNum() == colliding_obs->getInstNum())
					{
						if (&(*it) == latest_obs) latest_obs = NULL;
						it = _obstacles.erase(it);
						colliding_obs = NULL;
						break;
					}
					else
					{
						it++;
					}
				}
				if (_obstacles.empty()) { latest_obs = NULL; colliding_obs = NULL; }
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	

	return false;
		
}
void updateCollider(std::list<obstacle> & obstacles, int player_x)
{
	if (colliding_obs == NULL && obstacles.empty() != true)
	{
		colliding_obs = &(*obstacles.begin());
	}
	if (colliding_obs != NULL)
	{
		if (colliding_obs->getPosition().x < player_x && colliding_obs != last_scored_obs)
		{
			score++;
			std::cout << score << "\n";
			last_scored_obs = colliding_obs;
		}
	}
	if (!obstacles.empty())
	{
		std::list<obstacle>::iterator it = obstacles.begin();
		while ((*it).getPosition().x < player_x)
		{
			if ((*it).getPosition().x < -40)
			{
				int instNum = (*it).getInstNum();
				std::string append = std::to_string(instNum);
				entry::getManager().remove(obs_base + append, true);
				it++;
				obstacles.pop_front();
				if (obstacles.empty()) { latest_obs = NULL; colliding_obs = NULL; return; }
			}
			else
			{
				it++;
			}
			if (it == obstacles.end())
			{
				colliding_obs = NULL;
				return;
			}
		}
		colliding_obs = &(*it);
	}
	else
	{
		colliding_obs = NULL;
	}
}


void gamemaster::deleteAll()
{
	latest_obs = NULL;
	colliding_obs = NULL;
	if (!_obstacles.empty())
	{
		std::list<obstacle>::iterator it = _obstacles.begin();
		while (it != _obstacles.end())
		{
			int instNum = it->getInstNum();
			std::string append = std::to_string(instNum);
			entry::getManager().remove(obs_base + append, true);
			it = _obstacles.erase(it);
		}
	}

}
