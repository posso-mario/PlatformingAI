#include "stdafx.h"
#include "menu.h"


menu::menuaction menu::show(sf::RenderWindow& window)
{
	std::cout << "showing menu \n";
	//load menu texture from file
	sf::Texture texture;
	texture.loadFromFile("images/menusprite.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(395, 0);

	//Setup clickable regions

	menulist playButton;
	playButton.rect.top = 21;
	playButton.rect.height = 42;
	playButton.rect.left = 445;
	playButton.rect.width = 138;
	playButton.action = play;

	menulist optionsButton;
	playButton.rect.top = 94;
	playButton.rect.height = 42;
	playButton.rect.left = 445;
	playButton.rect.width = 138;
	playButton.action = options;

	menulist exitButton;
	exitButton.rect.left = 445;
	exitButton.rect.width = 138;
	exitButton.rect.top = 170;
	exitButton.rect.height = 42;
	exitButton.action = exit;

	_menuList.push_back(playButton);
	_menuList.push_back(optionsButton);
	_menuList.push_back(exitButton);

	window.clear();
	window.draw(sprite);
	window.display();

	return getMenuAction(window);
}

menu::menuaction menu::handleClick(int x, int y)
{
	std::list<menulist>::iterator it;

	for (it = _menuList.begin(); it != _menuList.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
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
				return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return exit;
			}
		}
	}
}