#include "stdafx.h"
#include "obstacle.h"
#include "entry.h"
#include "gamemaster.h"
#include <iostream>

obstacle::obstacle()
{

}

obstacle::~obstacle()
{

}

float obstacle::getVelocity() const
{
	return _velocity;
}

void obstacle::setVelocity(float velocity)
{
	_velocity = velocity;
}

int obstacle::getInstNum()
{
	return instNum;
}

void obstacle::setInstNum(int num)
{
	instNum = num;
}

void obstacle::update(float elapsedTime)
{
	visibleobj::setPosition(visibleobj::getPosition().x + _velocity*elapsedTime, visibleobj::getPosition().y);
}

void obstacle::load(obstacle_t Type)
{
	if (Type == good)
	{
		visibleobj::load("images/steaksprite.png");
		obstacle_height = 40;
		obstacle_width = 40;
	}
	else if (Type == bad)
		visibleobj::load("images/spikesprite.png");
}