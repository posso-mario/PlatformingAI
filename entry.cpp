#include "stdafx.h"
#include "entry.h"
#include "intro.h"



entry::gamestate entry::_gameState = uninitialized;
sf::RenderWindow entry::_mainWindow;
objmngr entry::_objectManager;
static intro * introobj = new intro();

void entry::start(void)
{
	if (_gameState != uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "AI-Platformer");

	_gameState = entry::gamestate::showingsplash;



	while (!isExiting())
	{
		gameLoop();
	}

	_mainWindow.close();
}

bool entry::isExiting()
{
	if (_gameState == entry::exiting)
		return true;
	else
		return false;
}

void entry::gameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent))
	{

		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = entry::exiting;
		}
		else 
		{
			switch (_gameState)
			{
			case entry::showingmenu:
			{
				menu * menuobj = new menu();
				menuobj->load("images/menusprite.png");
				menuobj->setPosition(395, 0);
				_objectManager.add("Menu", menuobj);
				_mainWindow.clear();
				_objectManager.drawAll(_mainWindow);
				_mainWindow.display();
				if (entry::handleMenu(menuobj) != menu::menuaction::nothing)
				{
					_objectManager.remove("Menu");
				}
				break;
			}
			case entry::showingsplash:
			{
				std::cout << "in showingsplash\n";
				introobj->load("images/introscreen.png");
				_objectManager.add("Intro", introobj);
				_mainWindow.clear();
				_objectManager.drawAll(_mainWindow);
				_mainWindow.display();
				introobj->onCreate(_mainWindow);
				_gameState = entry::showingmenu;
				break;
			}
			case entry::showingoptions:
			{
				break;
			}
			case entry::playing:
			{
				_mainWindow.clear(sf::Color(255, 0, 0));
				_mainWindow.display();
				while (1);
				break;
			}
			}
		}
		_objectManager.drawAll(_mainWindow);
		_mainWindow.display();
	}
}


menu::menuaction entry::handleMenu(menu * menuobj)
{
	menu::menuaction action = menuobj->getMenuAction(_mainWindow);
	switch (action)
	{
	case menu::menuaction::exit:
		_gameState = entry::exiting;
		break;
	case menu::menuaction::play:
		_gameState = entry::playing;
		break;
	case menu::menuaction::options:
		_gameState = entry::showingoptions;
		break;
	case menu::menuaction::nothing:
		std::cout << "Nothing \n";
		break;
	}
	return action;

}
