#pragma once
#include "visibleobj.h"

class objmngr
{
public:
	objmngr();
	~objmngr();

	void add(std::string name, visibleobj* gameObject);
	void remove(std::string name);
	int getObjectCount() const;
	visibleobj* get(std::string name) const;

	void drawAll(sf::RenderWindow& renderWindow);

private:
	std::map<std::string, visibleobj*> _gameObjects;

	struct objectdeallocator
	{
		void operator()(const std::pair<std::string, visibleobj*> & p) const
		{
			delete p.second;
		}
	};
};