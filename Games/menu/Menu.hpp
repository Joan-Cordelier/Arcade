/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Menu.hpp
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>
#include <string>
#include "../IGame.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"

class Menu : public IGame {
    public:
        Menu();
        ~Menu() override;

        void reset() override;
        void update(Event event) override;

        const std::vector<DisplayObject> getDisplayData() const override;

        int getScore() const override;
        void stop() override;
    private:
        std::vector<DisplayObject> _displayData;
        int _score;
        int _selectedIndex;
        std::vector<std::string> _games;
        std::vector<std::string> _displays;
        std::string _currentGame;
        std::string _currentDisplay;
};

extern "C" IGame* createGame();

#endif
