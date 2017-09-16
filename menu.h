#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "visibleobj.h"
#include <list>

class menu : public visibleobj
{
public:
 enum menuaction { nothing, exit, play, options };

 menu();

 ~menu();
 struct menulist
   {
   public:
    sf::Rect<int> rect;
	menuaction action;
   };

 menuaction getMenuAction(sf::RenderWindow& window);

 //menuaction show(sf::RenderWindow& window);

private:
 menuaction handleClick(int x, int y);
 std::list<menulist> _menuList;
 };