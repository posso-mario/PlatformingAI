#include "stdafx.h"
#include "menu.h"
#include <iostream>

menu::~menu()
{
	//_menuList.~list();
}

menu::menu()
{
	std::cout << "showing menu \n";
	//load menu texture from file
	/*sf::Texture texture;
	sf::Vector2u windowSize = window.getSize();
	texture.create(windowSize.x, windowSize.y);
	texture.update(window);
	sf::Sprite sprite(texture);
	sf::Texture texture2;
	texture2.loadFromFile("images/menusprite.png");
	sf::Sprite sprite2(texture2);
	
	
	sprite2.setPosition(395, 0);
*/
	//Setup clickable regions

	menulist playButton;
	playButton.rect.top = 21;
	playButton.rect.height = 42;
	playButton.rect.left = 445;
	playButton.rect.width = 138;
	playButton.action = play;

	menulist optionsButton;
	optionsButton.rect.top = 94;
	optionsButton.rect.height = 42;
	optionsButton.rect.left = 445;
	optionsButton.rect.width = 138;
	optionsButton.action = options;

	menulist exitButton;
	exitButton.rect.left = 445;
	exitButton.rect.width = 138;
	exitButton.rect.top = 170;
	exitButton.rect.height = 42;
	exitButton.action = exit;

	_menuList.push_back(optionsButton);
	_menuList.push_back(playButton);
	_menuList.push_back(exitButton);
	std::cout << "Size of list is: " << _menuList.size() << "\n";
/*
	window.clear();
	window.draw(sprite);
	window.draw(sprite2);
	window.display();
*/
}

void menu::load()
{
	visibleobj::load("images/menusprite.png");
}

menu::menuaction menu::handleClick(int x, int y)
{
	std::list<menulist>::iterator it;

	for (it = _menuList.begin(); it != _menuList.end(); it++)
	{
		std::cout << (*it).action << "\n";
		sf::Rect<int> menuItemRect = (*it).rect;
		std::cout << menuItemRect.top << "\n";
		if ((menuItemRect.top + menuItemRect.height) > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& (menuItemRect.left + menuItemRect.width) > x)
		{
			return (*it).action;
		}
	}

	return nothing;
}

menu::menuaction  menu::getMenuAction(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				menu::menuaction clickAction = handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				while (menuEvent.type != sf::Event::MouseButtonReleased)
				{
					window.pollEvent(menuEvent);
					//std::cout << "loop\n";
				}
				menu::menuaction clickAction2 = handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				if (clickAction == clickAction2) return(clickAction);
				else return (menu::menuaction::nothing);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return exit;
			}
		}
	}
}