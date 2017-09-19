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

void obstacle::update(float elapsedTime)
{

}

void obstacle::load(obstacle_t Type)
{
	if (Type == ground)
		visibleobj::load("images/obstacle_ground.png");
	else if (Type == air)
		visibleobj::load("images/obstacle_air.png");
}