/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** MenuManager.cpp
*/

#include "MenuManager.hpp"
#include "../Library_manager/LibraryManager.hpp"
#include "../Score_manager/ScoreManager.hpp"
#include <algorithm>

MenuManager::MenuManager(LibraryManager* libManager, ScoreManager* scoreManager)
    : inMenu(true), currentSection(GAMES), currentSelection(0),
      libraryManager(libManager), scoreManager(scoreManager)
{
    playerName = "Player";
}

void MenuManager::addPlayerNameChar(char c)
{
    if (c >= 32 && c <= 126) {
        playerName += c;
    }
}

void MenuManager::removePlayerNameChar()
{
    if (!playerName.empty()) {
        playerName.pop_back();
    }
}

void MenuManager::selectPreviousItem()
{
    switch (currentSection) {
        case GAMES:
            if (currentSelection > 0)
                currentSelection--;
            break;
        case GRAPHICS:
            if (currentSelection > 0)
                currentSelection--;
            break;
        case NAME_INPUT:
            break;
    }
}

void MenuManager::selectNextItem()
{
    switch (currentSection) {
        case GAMES:
            if (currentSelection < static_cast<int>(libraryManager->getGameLibs().size()) - 1)
                currentSelection++;
            break;
        case GRAPHICS:
            if (currentSelection < static_cast<int>(libraryManager->getDisplayLibs().size()) - 1)
                currentSelection++;
            break;
        case NAME_INPUT:
            break;
    }
}

void MenuManager::validateSelection()
{
    switch (currentSection) {
        case GAMES:
            if (!libraryManager->getGameLibs().empty()) {
                const auto& gameLibs = libraryManager->getGameLibs();
                if (currentSelection >= 0 && currentSelection < static_cast<int>(gameLibs.size())) {
                    libraryManager->loadGameLibrary(gameLibs[currentSelection]);
                    inMenu = false;
                }
            }
            break;
        case GRAPHICS:
            if (!libraryManager->getDisplayLibs().empty()) {
                const auto& displayLibs = libraryManager->getDisplayLibs();
                if (currentSelection >= 0 && currentSelection < static_cast<int>(displayLibs.size())) {
                    libraryManager->loadDisplayLibrary(displayLibs[currentSelection]);
                }
            }
            break;
        case NAME_INPUT:
            break;
    }
}

void MenuManager::handleMenuInput(const Event& event)
{
    if (event.type == EventType::KEY_PRESSED) {
        switch (event.key) {
            case Key::UP:
                selectPreviousItem();
                break;
            case Key::DOWN:
                selectNextItem();
                break;
            case Key::LEFT:
                if (currentSection == GRAPHICS)
                    currentSection = GAMES;
                else if (currentSection == NAME_INPUT)
                    currentSection = GRAPHICS;
                currentSelection = 0;
                break;
            case Key::RIGHT:
                if (currentSection == GAMES)
                    currentSection = GRAPHICS;
                else if (currentSection == GRAPHICS)
                    currentSection = NAME_INPUT;
                currentSelection = 0;
                break;
            case Key::ENTER:
                validateSelection();
                break;
            case Key::BACKSPACE:
                if (currentSection == NAME_INPUT) {
                    removePlayerNameChar();
                }
                break;
            default:
                if (currentSection == NAME_INPUT && event.key >= Key::A && event.key <= Key::Z) {
                    char c = 'a' + (static_cast<int>(event.key) - static_cast<int>(Key::A));
                    addPlayerNameChar(c);
                }
                break;
        }
    }
}

void MenuManager::renderMenu(IDisplay* display, const std::vector<std::string>& displayLibs, 
                         const std::vector<std::string>& gameLibs, int currentDisplayIndex, 
                         int currentGameIndex)
{
    drawText(display, 300, 10, "ARCADE");
    
    renderGamesSection(display, gameLibs, currentGameIndex);
    renderGraphicsSection(display, displayLibs, currentDisplayIndex);
    renderNameSection(display);
    renderScoresSection(display);
    renderControlsSection(display);
    //TODO: add sections for settings, help, etc.
    //TODO: maybe had scrolling...
}

void MenuManager::renderGamesSection(IDisplay* display, const std::vector<std::string>& gameLibs, int currentGameIndex)
{
    drawText(display, 10, 50, "GAMES");
    drawText(display, 10, 60, "------");
    
    const int startY = 80;
    const int spacing = 15;
    
    if (gameLibs.empty()) {
        drawText(display, 10, startY, "No games available");
        return;
    }
    
    for (size_t i = 0; i < gameLibs.size(); ++i) {
        std::string gameName = gameLibs[i].substr(6);
        gameName = gameName.substr(0, gameName.length() - 3);
        
        std::string prefix;
        if (currentSection == GAMES && static_cast<int>(i) == currentSelection)
            prefix = "> ";
        else if (static_cast<int>(i) == currentGameIndex)
            prefix = "* ";
        else
            prefix = "  ";
        
        drawText(display, 10, startY + i * spacing, prefix + gameName);
    }
}

void MenuManager::renderGraphicsSection(IDisplay* display, const std::vector<std::string>& displayLibs, int currentDisplayIndex)
{
    drawText(display, 250, 50, "GRAPHICS");
    drawText(display, 250, 60, "--------");
    
    const int startY = 80;
    const int spacing = 15;
    
    if (displayLibs.empty()) {
        drawText(display, 250, startY, "No display libs available");
        return;
    }
    
    for (size_t i = 0; i < displayLibs.size(); ++i) {
        std::string libName = displayLibs[i].substr(6);
        libName = libName.substr(0, libName.length() - 3);
        
        std::string prefix;
        if (currentSection == GRAPHICS && static_cast<int>(i) == currentSelection)
            prefix = "> ";
        else if (static_cast<int>(i) == currentDisplayIndex)
            prefix = "* ";
        else
            prefix = "  ";
        
        drawText(display, 250, startY + i * spacing, prefix + libName);
    }
}

void MenuManager::renderNameSection(IDisplay* display)
{
    drawText(display, 450, 50, "PLAYER NAME");
    drawText(display, 450, 60, "-----------");
    
    std::string nameField = playerName;
    if (currentSection == NAME_INPUT)
        nameField += "_"; //TODO: make it blink with a timer
    
    drawText(display, 450, 80, nameField);
}

void MenuManager::renderScoresSection(IDisplay* display)
{
    drawText(display, 10, 250, "HIGH SCORES");
    drawText(display, 10, 260, "-----------");

    std::vector<std::pair<std::string, int>> topScores;
    
    if (!libraryManager->getGameLibs().empty()) {
        const auto& gamePath = libraryManager->getGameLibs()[libraryManager->getCurrentGameIndex()];
        std::string gameName = gamePath.substr(6);
        gameName = gameName.substr(0, gameName.length() - 3);
        
        topScores = scoreManager->getFormattedScores(gameName);
    }
    
    const int startY = 280;
    const int spacing = 15; //TODO: change as needed
    
    if (topScores.empty()) {
        drawText(display, 10, startY, "No scores yet");
        return;
    }
    
    for (size_t i = 0; i < topScores.size() && i < 5; ++i) {
        std::string scoreText = topScores[i].first + ": " + std::to_string(topScores[i].second);
        drawText(display, 10, startY + (i * spacing), scoreText);
    }
}

void MenuManager::renderControlsSection(IDisplay* display)
{
    const int startY = 400;

    drawText(display, 10, startY, "CONTROLS");
    drawText(display, 10, startY + 10, "--------");
    drawText(display, 10, startY + 30, "F1: Next Display");
    drawText(display, 10, startY + 45, "F2: Next Game");
    drawText(display, 10, startY + 60, "F3: Restart Game");
    drawText(display, 10, startY + 75, "F4: Menu");
    drawText(display, 10, startY + 90, "ESC: Exit");
    drawText(display, 10, startY + 105, "Arrow keys: Navigate");
    drawText(display, 10, startY + 120, "Enter: Select");
}
