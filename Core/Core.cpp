/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** Core.cpp
*/

#include "Core.hpp"
#include "Library_manager/LibraryManager.hpp"
#include "Menu_manager/MenuManager.hpp"
#include "Score_manager/ScoreManager.hpp"
#include <iostream>
#include <stdexcept>

Core::Core(const std::string& initialLibrary) 
    : isRunning(false), display(nullptr), game(nullptr)
{
    try {
        libraryManager = std::make_unique<LibraryManager>();
        scoreManager = std::make_unique<ScoreManager>();
        menuManager = std::make_unique<MenuManager>(libraryManager.get(), scoreManager.get());

        display = libraryManager->loadDisplayLibrary(initialLibrary);
        
        if (display == nullptr) {
            throw std::runtime_error("Failed to load initial display library");
        }
    } catch (const std::exception& e) {
        if (display != nullptr) {
            display->stop();
            display = nullptr;
        }
        throw;
    }
}

Core::~Core()
{
    if (libraryManager != nullptr) {
        libraryManager->closeDisplayLibrary();
        libraryManager->closeGameLibrary();
    }
    if (menuManager != nullptr) {
        menuManager->setMenuState(false);
    }
    if (scoreManager != nullptr) {
        scoreManager->saveScores();
    }
    if (display != nullptr) {
        display->stop();
    }
    if (game != nullptr) {
        game->stop();
    }
}

void Core::run()
{
    if (display == nullptr) {
        throw std::runtime_error("No display library loaded");
    }

    if (game == nullptr) {
        try {
            game = libraryManager->loadGameLibrary("./lib/arcade_menu.so");
        } catch (const std::exception& e) {
            std::cerr << "Error loading menu: " << e.what() << std::endl;
            isRunning = false;
            return;
        }
    }    
    
    display->init(800, 600); //TODO: change it to xhat we want
    
    isRunning = true;
    
    while (isRunning) {
        Event event = display->pollEvent();

        if (event.type == EventType::KEY_PRESSED && event.key == Key::ESCAPE) {
            isRunning = false;
            continue;
        }
        if (menuManager->isInMenu()) {
            menuManager->handleMenuInput(event);
        } else if (game != nullptr) {
            game->update(event);
        }

        update();
    }
    exitGame();
}

void Core::update()
{
    if (display == nullptr) {
        return;
    }
    
    display->clear();
    
    if (menuManager->isInMenu()) {
        menuManager->renderMenu(
            display,
            libraryManager->getDisplayLibs(),
            libraryManager->getGameLibs(),
            libraryManager->getCurrentDisplayIndex(),
            libraryManager->getCurrentGameIndex()
        );
    } else if (game != nullptr) {
        const auto& gameObjects = game->getDisplayData();

        display->display(gameObjects);
    }
    
    display->display({});
}

void Core::nextDisplay()
{
    try {
        display = libraryManager->nextDisplay();
        if (display != nullptr) {
            display->init(800, 600);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error switching display: " << e.what() << std::endl;
    }
}

void Core::nextGame()
{
    try {
        game = libraryManager->nextGame();
        if (game != nullptr) {
            menuManager->setMenuState(false);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error switching game: " << e.what() << std::endl;
    }
}

void Core::restartGame()
{
    if (game != nullptr) {
        game->reset();
    }
}

void Core::goToMenu()
{
    menuManager->setMenuState(true);
}

void Core::exitGame()
{
    if (game != nullptr) {
        game->stop();
        game = nullptr;
    }
    if (display != nullptr) {
        display->stop();
        display = nullptr;
    }
    if (libraryManager != nullptr) {
        libraryManager->closeDisplayLibrary();
        libraryManager->closeGameLibrary();
    }
    if (menuManager != nullptr) {
        menuManager->setMenuState(false);
    }
    if (scoreManager != nullptr) {
        scoreManager->saveScores();
    }
    isRunning = false;
}
