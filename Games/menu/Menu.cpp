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
    if (event.type == EventType::KEY_PRESSED) {
        switch (event.key) {
            case Key::UP:
                _selectedIndex = (_selectedIndex - 1 + _games.size()) % _games.size();
                break;
            case Key::DOWN:
                _selectedIndex = (_selectedIndex + 1) % _games.size();
                break;
            case Key::ENTER:
                _currentGame = _games[_selectedIndex];
                break;
            default:
                break;
        }
    }
}

const std::vector<DisplayObject> Menu::getDisplayData() const
{
    std::vector<DisplayObject> displayData;

    // Titre
    displayData.push_back(DisplayObject(10, 2, 1, 1, ObjectType::TEXT, 
        Color(255, 255, 255), "=== MENU ==="));

    // Liste des jeux
    for (size_t i = 0; i < _games.size(); ++i) {
        std::string text = (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + _games[i];
        displayData.push_back(DisplayObject(10, 4 + i, 1, 1, ObjectType::TEXT, 
            Color(0, 255, 0), text));
    }

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
