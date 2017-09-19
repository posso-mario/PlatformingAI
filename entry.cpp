#include "stdafx.h"
#include "entry.h"
#include "intro.h"
#include "player.h"



entry::gamestate entry::_gameState = uninitialized;
sf::RenderWindow entry::_mainWindow;
objmngr entry::_objectManager;
sf::Keyboard entry::_keyboard;
static intro * introobj = new intro();
menu::menuaction lastAction;
player * playerobj;

void entry::start(void)
{
	if (_gameState != uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "AI-Platformer");
	_mainWindow.setFramerateLimit(30);
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

sf::RenderWindow & entry::getWindow()
{
	return _mainWindow;
}

sf::Keyboard & entry::getInput()
{
	return _keyboard;
}

objmngr & entry::getManager()
{
	return _objectManager;
}

void entry::gameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent) || true)
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
				menu * menuobj;
				std::cout << "in showingmenu\n";
				if (_objectManager.get("Menu") == NULL)
				{
					menuobj = new menu();
					menuobj->load();
					menuobj->setPosition(395, 0);
					_objectManager.add("Menu", menuobj);
				}
				menuobj = dynamic_cast<menu *>(_objectManager.get("Menu"));
				_mainWindow.clear();
				_objectManager.drawAll(_mainWindow);
				_mainWindow.display();
				lastAction = entry::handleMenu(menuobj);
				if ( lastAction != menu::menuaction::nothing)
				{
					_objectManager.remove("Menu");
				}
				break;
			}
			case entry::showingsplash:
			{
				std::cout << "in showingsplash\n";
				introobj->load();
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
				std::cout << "playing\n";
				if (_objectManager.get("Player") == NULL)
				{
					playerobj = new player();
					playerobj->load();
					playerobj->setPosition(420, 0);
					_objectManager.add("Player", playerobj);
				}
				_mainWindow.clear();
				_objectManager.drawAll(_mainWindow);
				_mainWindow.display();
				_objectManager.updateAll();
				
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
	std::cout << action << "\n";
	switch (action)
	{
	case menu::menuaction::exit:
		_gameState = entry::exiting;
		break;
	case menu::menuaction::play:
		_gameState = entry::playing;
		std::cout << "playing\n";
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
