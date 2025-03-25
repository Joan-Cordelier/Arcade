/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Arcade.hpp
*/

#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include "../Display/IDisplay.hpp"
#include "../Games/IGame.hpp"

enum Graphique {
    NCURSE,
    SDL2
};

enum Game {
    MENU
};


class Arcade {
    private:
        Graphique _currentGraph_enum;
        Game _currentGame_enum;

        int event;

        const char *_currentGraph;
        const char *_currentGame;

        IGame *_game;
        IDisplay *_display;

    public:
        Arcade(std::string library);
        ~Arcade();
        void RunGame();
        void VerifType();

        bool ChargeLibGame();
        bool ChargeLibGraphique();

        void SetCurrentGraph(std::string type);
        void SetCurrentGraph(Graphique type);

        void SetCurrentGame(std::string game);
        void SetCurrentGame(Game game);

        Graphique GetCurrentGraph();
        Game GetCurrentGame();

};
