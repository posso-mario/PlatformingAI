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
	virtual void update(float elapsedTime);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;

	bool handledCreate = false;

protected:
	sf::Sprite & getSprite();

private:
	sf::Sprite  _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;

};