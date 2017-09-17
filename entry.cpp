#include "stdafx.h"
#include "entry.h"
#include "intro.h"



entry::gamestate entry::_gameState = uninitialized;
sf::RenderWindow entry::_mainWindow;
menu entry::_menu;

void entry::start(void)
{
	if (_gameState != uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "AI-Platformer");
	_menu.load("images/menusprite.png");
	_menu.setPosition(395, 0);
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
				showMenuSprite();
				break;
			}
			case entry::showingsplash:
			{
				showIntroScreen();
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
				break;
			}
			}
		}
	}
}

void entry::showIntroScreen()
{
	intro introScreen;
	introScreen.show(_mainWindow);
	_gameState = entry::showingmenu;
	return;
}

void entry::showMenuSprite()
{
	_menu.draw(_mainWindow);
	_mainWindow.display();
	menu::menuaction action = _menu.getMenuAction(_mainWindow);
	switch (action)
	{
	case menu::exit:
		_gameState = entry::exiting;
		break;
	case menu::play:
		_gameState = entry::playing;
		break;
	case menu::options:
		_gameState = entry::showingoptions;
		break;
	case menu::nothing:
		std::cout << "Nothing \n";
		break;
	}
}