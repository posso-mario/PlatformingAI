#include "StdAfx.h"
#include "visibleobj.h"


visibleobj::visibleobj()
{
	_isLoaded = false;
}


visibleobj::~visibleobj()
{
}

sf::Sprite & visibleobj::getSprite()
{
	return _sprite;
}

sf::Vector2f visibleobj::getPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

bool visibleobj::isLoaded() const
{
	return _isLoaded;
}

void visibleobj::update(float elapsedTime)
{
}

void visibleobj::onCreate(sf::RenderWindow & window)
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