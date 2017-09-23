#include "stdafx.h"
#include "entry.h"
#include "intro.h"
#include "player.h"
#include "gamemaster.h"



entry::gamestate entry::_gameState = uninitialized;
sf::RenderWindow entry::_mainWindow;
objmngr entry::_objectManager;
sf::Keyboard entry::_keyboard;
//static intro * introobj = new intro();
menu::menuaction lastAction;
player * playerobj;
bool firstObs = false;
gamemaster entry::_gameMaster;
bool entry::isDead;

void entry::start(void)
{
	isDead = false;
	if (_gameState != uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "AI-Platformer");
	_mainWindow.setFramerateLimit(60);
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

gamemaster & entry::getGM()
{
	return _gameMaster;
}

void entry::setDeath()
{
	isDead = true;
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
				//std::cout << "in showingmenu\n";
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
					_objectManager.remove("Menu", false);
				}
				break;
			}
			case entry::showingsplash:
			{
				intro * introobj;
				//std::cout << "in showingsplash\n";
				if (_objectManager.get("Intro") == NULL)
				{
					introobj = new intro();
					introobj->load();
					_objectManager.add("Intro", introobj);
					_mainWindow.clear();
					_objectManager.drawAll(_mainWindow);
					_mainWindow.display();
					introobj->onCreate(_mainWindow);
					_gameState = entry::showingmenu;
				}
				
				break;
			}
			case entry::showingoptions:
			{
				break;
			}
			case entry::playing:
			{
				//std::cout << "playing\n";
				if (_objectManager.get("Player") == NULL)
				{
					playerobj = new player();
					playerobj->load();
					playerobj->setPosition(380, 668);
					_objectManager.add("Player", playerobj);
					_gameMaster.registerPlayer(playerobj);
				}
				
				_gameMaster.createObstacle();
				_mainWindow.clear();
				_objectManager.drawAll(_mainWindow);
				_mainWindow.display();
				_objectManager.updateAll();
				if (isDead)
				{
					isDead = false;
					_gameMaster.deleteAll();
					_objectManager.removeAll();
					_gameState = entry::showingsplash;
				}
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
