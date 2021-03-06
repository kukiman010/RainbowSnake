#include "MenuState.h"
#include <iostream>



MenuState::MenuState(int STATE_ID, RenderWindow& window, Font& font)
	:State(STATE_ID,window,font)
{
}


MenuState::~MenuState()
{
}

void MenuState::init()
{
	rainbowTextInit();
	titleInit();
	menuOptionsInit();
}

void MenuState::rainbowTextInit()
{
	char title[] = { "RAINBOW" };
	for (int i = 0; i < 7; i++)
	{
		rainbow[i].setString(string(1, title[i]));
		rainbow[i].setFont(*_font);
		rainbow[i].setCharacterSize(86);
		if (i == 0) rainbow[i].setPosition(Vector2f(24, (float)Game::APPLE_SIZE / 2.f));
		else rainbow[i].setPosition(Vector2f(rainbow[i - 1].getGlobalBounds().left + rainbow[i - 1].getGlobalBounds().width + 4, (float)Game::APPLE_SIZE / 2.f));
	}

	int alpha = 205;
	rainbow[0].setColor(Color(255, 0, 0, alpha));
	rainbow[1].setColor(Color(255, 255, 0, alpha));
	rainbow[2].setColor(Color(0, 255, 0, alpha));
	rainbow[3].setColor(Color(0, 255, 255, alpha));
	rainbow[4].setColor(Color(0, 0, 255, alpha));
	rainbow[5].setColor(Color(128, 0, 255, alpha));
	rainbow[6].setColor(Color(255, 0, 255, alpha));
}

void MenuState::titleInit()
{
	title.setString("SNAKE");
	title.setFont(*_font);
	title.setCharacterSize(86);
	title.setColor(Color::Cyan);
	title.setPosition(Vector2f(rainbow[6].getPosition().x + rainbow[6].getGlobalBounds().width + 16, (float)Game::APPLE_SIZE / 2.f));
}

void MenuState::menuOptionsInit()
{
	const int howManyMenuOptions = 2;

	string menuOptionsStrings[howManyMenuOptions] = { "PLAY", "EXIT" };
	for (int i = 0; i < howManyMenuOptions; i++)
	{
		menuOptions[i].setString(menuOptionsStrings[i]);
		menuOptions[i].setFont(*_font);
		menuOptions[i].setCharacterSize(64);
		menuOptions[i].setColor(Color::White);
		menuOptions[i].setOrigin(Vector2f(menuOptions[i].getGlobalBounds().width / 2.f, menuOptions[i].getGlobalBounds().height / 2.f));
		menuOptions[i].setPosition(Vector2f((float)Game::SCRN_WIDTH / 2.f, (float)Game::SCRN_HEIGHT / 2.f - (float)32 + 2.5*(float)i*(float)32));
	}
}

int MenuState::handleEvents(Event& event)
{
	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	while (_window->pollEvent(event))
	{
		if (event.type == Event::Closed || (event.type == Event::MouseButtonReleased && menuOptions[1].getGlobalBounds().contains(mousePosition)))
			return Game::END;

		else if (event.type == Event::MouseButtonReleased && menuOptions[0].getGlobalBounds().contains(mousePosition))
			return Game::PLAY_STATE;
	}

	return STATE_ID;
}

void MenuState::update()
{
	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	for (int i = 0; i < 2; i++) 
	{
		if (menuOptions[i].getGlobalBounds().contains(mousePosition))
		{
			menuOptions[i].setColor(Color::Cyan);
		}
		else menuOptions[i].setColor(Color::White);
	}
}

void MenuState::render()
{
	_window->clear();

	for (int i = 0; i < 7; i++)
		_window->draw(rainbow[i]);

	_window->draw(title);

	for (int i = 0; i < 2; i++)
		_window->draw(menuOptions[i]);

	_window->display();

}