/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** Core.hpp
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "../Display/IDisplay.hpp"
#include "../Games/IGame.hpp"

// Forward declarations of subclasses
class LibraryManager;
class MenuManager;
class ScoreManager;

class Core {
    public:
        Core(const std::string& initialLibrary);
        ~Core();

        void run();
        void update();
        
        void nextDisplay();
        void nextGame();
        void restartGame();
        void goToMenu();
        void exitGame();

    private:
        std::unique_ptr<LibraryManager> libraryManager;
        std::unique_ptr<MenuManager> menuManager;
        std::unique_ptr<ScoreManager> scoreManager;

        bool isRunning;
        bool pauseMenuRendered;

        IDisplay* display;
        IGame* game;

        void saveCurrentScore();
};