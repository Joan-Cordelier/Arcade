/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Menu.cpp
*/

#include "Menu.hpp"


Menu::Menu()
{
    _score = 0;
    _selectedIndex = 0;
    _games = {"Game1", "Game2", "Game3"};
    _displays = {"Display1", "Display2", "Display3"};
    _currentGame = _games[0];
    _currentDisplay = _displays[0];
}

Menu::~Menu()
{
}

void Menu::reset()
{
    _score = 0;
    _selectedIndex = 0;
    _currentGame = _games[0];
    _currentDisplay = _displays[0];
}

void Menu::update(Event event)
{
}

const std::vector<DisplayObject> Menu::getDisplayData() const
{
    std::vector<DisplayObject> displayData;
    return displayData;
}

int Menu::getScore() const
{
    return _score;
}

void Menu::stop()
{
}

extern "C" IGame* createGame()
{
    return new Menu();
}
