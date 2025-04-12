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
        std::cerr << "Exception in Core constructor: " << e.what() << std::endl;
        if (display != nullptr) {
            display->stop();
            display = nullptr;
        }
        throw;
    }
}

Core::~Core()
{
    exitGame();
}

void Core::run()
{
    if (display == nullptr) {
        throw std::runtime_error("No display library loaded");
    }
    if (menuManager == nullptr) {
        throw std::runtime_error("No menu manager initialized");
    }
    if (libraryManager == nullptr) {
        throw std::runtime_error("No library manager initialized");
    }
    if (scoreManager == nullptr) {
        throw std::runtime_error("No score manager initialized");
    }
    
    try {
        display->init(800, 600);
        isRunning = true;

        while (isRunning) {
            Event event = display->pollEvent();

            if (event.type == EventType::KEY_PRESSED && event.key == Key::ESCAPE) {
                if (menuManager->isInMenu())
                    isRunning = false;
                else
                    menuManager->setMenuState(true);
                continue;
            }

            if (event.type == EventType::KEY_PRESSED && event.key == Key::F1) {
                nextDisplay();
                continue;
            }

            if (event.type == EventType::KEY_PRESSED && event.key == Key::F2) {
                nextGame();
                continue;
            }

            if (menuManager->isInMenu()) {
                menuManager->update(event);
                if (menuManager->getNextDisplay()) {
                    nextDisplay();
                    menuManager->setNextDisplay(false);
                }

                if (!menuManager->isInMenu()) {
                    try {
                        game = libraryManager->loadGameLibrary(
                            libraryManager->getCurrentGameName());
                    } catch (const std::exception& e) {
                        std::cerr << "Error loading game: " << e.what() << std::endl;
                        menuManager->setMenuState(true);
                    }
                }
            } else if (game != nullptr) {
                game->update(event);
            }

            update();
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in Core::run: " << e.what() << std::endl;
    }

    exitGame();
}

void Core::update()
{
    if (display == nullptr)
        return;

    display->clear();

    if (menuManager->isInMenu()) {
        auto menuObjects = menuManager->getDisplayData();
        display->display(menuObjects);
    } else if (game != nullptr) {
        auto objects = game->getDisplayData();
        std::string scoreText = "Score: " + std::to_string(game->getScore());
        DisplayObject scoreDisplay(40, 10, 10, 2, ObjectType::TEXT, Color(255, 255, 0), scoreText);
        scoreDisplay.setScaleX(1.0f);
        scoreDisplay.setScaleY(1.0f);
        objects.push_back(scoreDisplay);

        display->display(objects);
    }
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
    isRunning = false;
    
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
}
