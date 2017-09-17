#pragma once
#include "stdafx.h"

class visibleobj
{
public:
	visibleobj();
	virtual ~visibleobj();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow & window);
	virtual void onCreate(sf::RenderWindow & window);
	virtual void setPosition(float x, float y);

	bool handledCreate = false;

private:
	sf::Sprite  _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;

};