#include "stdafx.h"
#include "objmngr.h"
#include "entry.h"




objmngr::objmngr()
{

}

objmngr::~objmngr()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), objectdeallocator());
}

void objmngr::add(std::string name, visibleobj* gameObject)
{
	_gameObjects.insert(std::pair<std::string, visibleobj*>(name, gameObject));
}

void objmngr::remove(std::string name)
{
	std::map<std::string, visibleobj*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

visibleobj* objmngr::get(std::string name) const
{
	std::map<std::string, visibleobj*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int objmngr::getObjectCount() const
{
	return _gameObjects.size();
}


void objmngr::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, visibleobj*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		/*if(itr->second->handledCreate == false)
		{
			itr->second->onCreate(renderWindow);
			itr = _gameObjects.begin();
			continue;
		}*/
		itr++;
	}
}

void objmngr::updateAll()
{
	std::map<std::string, visibleobj*>::const_iterator itr =_gameObjects.begin();
	sf::Time timeDelta = clock.getElapsedTime();

	while (itr != _gameObjects.end())
	{
		//std::cout << "updating\n";
		itr->second->update(timeDelta.asSeconds());
		itr++;
	}

	clock.restart();

}
