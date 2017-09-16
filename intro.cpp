#include "stdafx.h"
#include "intro.h"

void intro::show(sf::RenderWindow & window)
{
	std::cout << "printing intro\n";
	sf::Texture texture;
	if (texture.loadFromFile("images/introscreen.png") != true)
	{
		return;
	}
	sf::Sprite sprite(texture);

	window.draw(sprite);
	window.display();

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