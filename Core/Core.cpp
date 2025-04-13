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
    : isRunning(false), pauseMenuRendered(false), display(nullptr), game(nullptr)
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

            if (event.type == EventType::KEY_PRESSED) {
                switch (event.key) {
                    case Key::Q:
                        if (!menuManager->isInMenu()) {
                            isRunning = false;
                            continue;
                        }
                        break;
                    case Key::ESCAPE:
                        if (menuManager->isInMenu())
                            isRunning = false;
                        else if (menuManager->isInPauseMenu()) {
                            menuManager->setPauseMenuState(false);
                            goToMenu();
                        } else
                            goToMenu();
                        continue;
                    case Key::F1:
                        nextDisplay();
                        continue;
                    case Key::F3:
                        if (!menuManager->isInMenu()) {
                            nextGame();
                        }
                        continue;
                    case Key::R:
                        if (!menuManager->isInMenu()) {
                            if (menuManager->isInPauseMenu()) {
                                menuManager->setPauseMenuState(false);
                                pauseMenuRendered = false;
                            }
                            restartGame();
                        }
                        continue;
                    case Key::P:
                        if (!menuManager->isInMenu()) {
                            menuManager->togglePauseMenu();
                            pauseMenuRendered = false;
                        }
                    default:
                        break;
                }
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
            } else if (game != nullptr && !menuManager->isInPauseMenu()) {
                game->update(event);
            }

            if (!pauseMenuRendered)
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
    } else {
        if (game != nullptr && !pauseMenuRendered) {
            auto objects = game->getDisplayData();
            
            std::string playerNameText = "Player: " + menuManager->getPlayerName();
            DisplayObject playerNameDisplay(40, 8, playerNameText.length(), 2, ObjectType::TEXT, Color(255, 255, 255), playerNameText);
            playerNameDisplay.setScaleX(1.0f);
            playerNameDisplay.setScaleY(1.0f);
            objects.push_back(playerNameDisplay);
            
            std::string scoreText = "Score: " + std::to_string(game->getScore());
            DisplayObject scoreDisplay(40, 10, 10, 2, ObjectType::TEXT, Color(255, 255, 0), scoreText);
            scoreDisplay.setScaleX(1.0f);
            scoreDisplay.setScaleY(1.0f);
            objects.push_back(scoreDisplay);

            display->display(objects);

            if (menuManager->isInPauseMenu()) {
                auto pauseMenuObjects = menuManager->getPauseMenuDisplayData();
                display->display(pauseMenuObjects);
                pauseMenuRendered = true;
            }
        }
    }
}

void Core::nextDisplay()
{
    pauseMenuRendered = false;

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
    saveCurrentScore();
    
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
    saveCurrentScore();

    if (game != nullptr) {
        if (menuManager->isInPauseMenu()) {
            menuManager->setPauseMenuState(false);
            pauseMenuRendered = false;
        }
        game->reset();
    }
}

void Core::goToMenu()
{
    saveCurrentScore();
    
    if (menuManager->isInPauseMenu()) {
        menuManager->setPauseMenuState(false);
        pauseMenuRendered = false;
    }
    menuManager->setMenuState(true);
}

void Core::saveCurrentScore()
{
    if (game != nullptr && !menuManager->isInMenu()) {
        int currentScore = game->getScore();
        std::string playerName = menuManager->getPlayerName();
        std::string gameName = libraryManager->getCurrentGameName();
        
        if (currentScore > 0 && !playerName.empty() && !gameName.empty()) {
            scoreManager->addScore(playerName, gameName, currentScore);
        }
    }
}

void Core::exitGame()
{
    isRunning = false;
    
    // Save score before exiting
    saveCurrentScore();
    
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

    pauseMenuRendered = false;
}
