#include "StdAfx.h"
#include "visibleobj.h"


visibleobj::visibleobj()
{
	_isLoaded = false;
}


visibleobj::~visibleobj()
{
}

void visibleobj::load(std::string filename)
{
	if (_texture.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void visibleobj::draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void visibleobj::setPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}