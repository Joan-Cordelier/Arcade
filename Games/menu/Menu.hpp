/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** Menu
*/

#include "../IGame.hpp"

#ifndef MENU_HPP_
#define MENU_HPP_

class Menu : public IGame {
    public:
        Menu();
        ~Menu() = default;

        void Play() override;
        void DoEvent(int event) override;

    protected:
    private:
};

extern "C" IGame* createGame() {
    return new Menu();
}

#endif /* !MENU_HPP_ */
