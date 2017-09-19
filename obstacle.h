#pragma once
#include "stdafx.h"
#include "visibleobj.h"

class obstacle : public visibleobj
{
public:
	int obstacle_width = 300;
	int obstacle_height = 150;

	enum obstacle_t {air, ground};

	obstacle();

	~obstacle();

	void update(float elapsedTime);

	float getVelocity() const;

	void load(obstacle_t type);
	
private:
	float _velocity;
	obstacle_t currentType;
};