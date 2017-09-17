#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "menu.h"
#include "objmngr.h"


class entry
{

public:
	static void start();

private:
	//static sf::Texture entry::globalTexture;

	static bool isExiting();
	static void gameLoop();
	static void showIntroScreen();
	static menu::menuaction handleMenu(menu * menuobj);

	enum gamestate {
		uninitialized, showingsplash, paused,
		showingmenu, playing, exiting, showingoptions
	};

	static gamestate _gameState;
	static sf::RenderWindow _mainWindow;
	static objmngr _objectManager;
};
