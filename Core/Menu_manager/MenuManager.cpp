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
    : inMenu(true), _nextDisplay(false), currentSection(GAMES), currentSelection(0),
      libraryManager(libManager), scoreManager(scoreManager)
{
    playerName = "Player";
}

void MenuManager::addPlayerNameChar(Key key)
{
    switch (key) {
        case Key::A: playerName += 'A'; break;
        case Key::B: playerName += 'B'; break;
        case Key::C: playerName += 'C'; break;
        case Key::D: playerName += 'D'; break;
        case Key::E: playerName += 'E'; break;
        case Key::F: playerName += 'F'; break;
        case Key::G: playerName += 'G'; break;
        case Key::H: playerName += 'H'; break;
        case Key::I: playerName += 'I'; break;
        case Key::J: playerName += 'J'; break;
        case Key::K: playerName += 'K'; break;
        case Key::L: playerName += 'L'; break;
        case Key::M: playerName += 'M'; break;
        case Key::N: playerName += 'N'; break;
        case Key::O: playerName += 'O'; break;
        case Key::P: playerName += 'P'; break;
        case Key::Q: playerName += 'Q'; break;
        case Key::R: playerName += 'R'; break;
        case Key::S: playerName += 'S'; break;
        case Key::T: playerName += 'T'; break;
        case Key::U: playerName += 'U'; break;
        case Key::V: playerName += 'V'; break;
        case Key::W: playerName += 'W'; break;
        case Key::X: playerName += 'X'; break;
        case Key::Y: playerName += 'Y'; break;
        case Key::Z: playerName += 'Z'; break;
        case Key::SPACE: playerName += ' '; break;
        case Key::NUM0: playerName += '0'; break;
        case Key::NUM1: playerName += '1'; break;
        case Key::NUM2: playerName += '2'; break;
        case Key::NUM3: playerName += '3'; break;
        case Key::NUM4: playerName += '4'; break;
        case Key::NUM5: playerName += '5'; break;
        case Key::NUM6: playerName += '6'; break;
        case Key::NUM7: playerName += '7'; break;
        case Key::NUM8: playerName += '8'; break;
        case Key::NUM9: playerName += '9'; break;
        default:
            break;
    }
}

void MenuManager::removePlayerNameChar()
{
    if (!playerName.empty()) {
        playerName.pop_back();
    }
}

void MenuManager::selectNextItem()
{
    switch (currentSection) {
        case GAMES:
            libraryManager->nextGame();
            currentSelection = libraryManager->getCurrentGameIndex();
            break;
        case GRAPHICS:
            currentSelection = libraryManager->getCurrentDisplayIndex();
            _nextDisplay = true;
            break;
        case NAME_INPUT:
            break;
    }
}

void MenuManager::update(Event event)
{
    if (event.type == EventType::KEY_PRESSED) {
        switch (event.key) {
            case Key::UP:
                currentSection = static_cast<MenuSection>(static_cast<int>(currentSection) - 1);
                if (currentSection < GAMES)
                    currentSection = NAME_INPUT;
                break;
            case Key::DOWN:
                currentSection = static_cast<MenuSection>(static_cast<int>(currentSection) + 1);
                if (currentSection > NAME_INPUT)
                    currentSection = GAMES;
                break;
            case Key::LEFT:
            case Key::RIGHT:
                selectNextItem();
                break;
            case Key::ENTER:
                if (currentSection == NAME_INPUT || currentSection == GAMES) {
                    inMenu = false;
                }
                break;
            case Key::BACKSPACE:
                if (currentSection == NAME_INPUT)
                    removePlayerNameChar();
                break;
            default:
                if (currentSection == NAME_INPUT) {
                    addPlayerNameChar(event.key);
                }
                break;
        }
    }
}

const std::vector<DisplayObject> MenuManager::getDisplayData() const
{
    std::vector<DisplayObject> displayData;

    // Draw borders
    for (int x = 0; x < _width; ++x) {
        DisplayObject topWall(x, 0, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        topWall.setScaleX(1);
        topWall.setScaleY(1);
        displayData.push_back(topWall);

        DisplayObject bottomWall(x, _height - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        bottomWall.setScaleX(1);
        bottomWall.setScaleY(1);
        displayData.push_back(bottomWall);
    }

    for (int y = 0; y < _height; ++y) {
        DisplayObject leftWall(0, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        leftWall.setScaleX(1);
        leftWall.setScaleY(1);
        displayData.push_back(leftWall);

        DisplayObject rightWall(_width - 1, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        rightWall.setScaleX(1);
        rightWall.setScaleY(1);
        displayData.push_back(rightWall);
    }
    
    // Draw menu title
    DisplayObject title(_width / 2 - 8, 5, 16, 2, ObjectType::TEXT, Color(255, 255, 0), "ARCADE MENU");
    displayData.push_back(title);
    
    // Draw Games section
    Color gameColor = (currentSection == GAMES) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject gamesTitle(5, 10, 10, 1, ObjectType::TEXT, gameColor, "GAMES:");
    displayData.push_back(gamesTitle);
    
    std::string currentGame = libraryManager->getCurrentGameName();
    DisplayObject gameValue(20, 10, currentGame.length(), 1, ObjectType::TEXT, gameColor, currentGame);
    displayData.push_back(gameValue);
    
    // Draw Graphics section
    Color graphicsColor = (currentSection == GRAPHICS) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject graphicsTitle(5, 15, 10, 1, ObjectType::TEXT, graphicsColor, "GRAPHICS:");
    displayData.push_back(graphicsTitle);
    
    std::string currentDisplay = libraryManager->getCurrentDisplayName();
    DisplayObject graphicsValue(20, 15, currentDisplay.length(), 1, ObjectType::TEXT, graphicsColor, currentDisplay);
    displayData.push_back(graphicsValue);
    
    // Draw Name Input section
    Color nameColor = (currentSection == NAME_INPUT) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject nameTitle(5, 20, 10, 1, ObjectType::TEXT, nameColor, "NAME:");
    displayData.push_back(nameTitle);
    
    DisplayObject nameValue(20, 20, playerName.length(), 1, ObjectType::TEXT, nameColor, playerName);
    displayData.push_back(nameValue);
    
    // Instructions
    DisplayObject instructions(5, 30, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "UP/DOWN: Select section, LEFT/RIGHT: Change option");
    displayData.push_back(instructions);
    DisplayObject instructions2(5, 32, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "ENTER: Start with selected options");
    displayData.push_back(instructions2);
    
    return displayData;
}
