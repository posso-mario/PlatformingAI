#include "stdafx.h"
#include "intro.h"

intro::intro()
{

}

intro::~intro()
{

}

void intro::load()
{
	visibleobj::load("images/introscreen.png");
}

void intro::onCreate(sf::RenderWindow & window)
{
	std::cout << "printing intro\n";
	sf::Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}