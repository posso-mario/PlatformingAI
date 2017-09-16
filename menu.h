#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class menu
{
public:
 enum menuaction { nothing, exit, play, options };

 struct menulist
   {
   public:
    sf::Rect<int> rect;
	menuaction action;
   };

 menuaction show(sf::RenderWindow& window);

private:
 menuaction getMenuAction(sf::RenderWindow& window);
 menuaction handleClick(int x, int y);
 std::list<menulist> _menuList;
 };