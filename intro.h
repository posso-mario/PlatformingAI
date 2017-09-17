#pragma once
#include "visibleobj.h"

class intro : public visibleobj
{
public:
	intro();
	~intro();
	void onCreate(sf::RenderWindow & window);
};