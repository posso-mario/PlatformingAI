#pragma once
#include "visibleobj.h"

class intro : public visibleobj
{
public:
	intro();
	~intro();
	void load();
	void onCreate(sf::RenderWindow & window);
};