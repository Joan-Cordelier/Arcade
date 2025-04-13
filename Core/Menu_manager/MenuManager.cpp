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
    : inMenu(true), inPauseMenu(false), _nextDisplay(false), currentSection(GAMES), currentSelection(0),
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

    // Draw borders - fix bottom and right walls to ensure they're visible
    int borderWidth = _width;
    int borderHeight = _height;
    
    // Draw top and bottom borders
    for (int x = 0; x < borderWidth; ++x) {
        DisplayObject topWall(x, 0, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        displayData.push_back(topWall);

        DisplayObject bottomWall(x, borderHeight - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        displayData.push_back(bottomWall);
    }

    // Draw left and right borders
    for (int y = 0; y < borderHeight; ++y) {
        DisplayObject leftWall(0, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        displayData.push_back(leftWall);

        DisplayObject rightWall(borderWidth - 1, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        displayData.push_back(rightWall);
    }
    
    // Adjusted positions for menu elements to ensure they stay within borders
    int menuCenterX = borderWidth / 2;
    // int menuWidth = borderWidth - 4;  // Keep elements away from borders
    int menuItemLeftMargin = 5;
    int menuItemRightMargin = menuItemLeftMargin + 15;
    
    // Draw menu title
    std::string titleText = "ARCADE MENU";
    DisplayObject title(menuCenterX - titleText.length()/2, 5, titleText.length(), 2, ObjectType::TEXT, Color(255, 255, 0), titleText);
    displayData.push_back(title);
    
    // Draw Games section
    Color gameColor = (currentSection == GAMES) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject gamesTitle(menuItemLeftMargin, 10, 10, 1, ObjectType::TEXT, gameColor, "GAMES:");
    displayData.push_back(gamesTitle);
    
    std::string currentGame = libraryManager->getCurrentGameName();
    DisplayObject gameValue(menuItemRightMargin, 10, currentGame.length(), 1, ObjectType::TEXT, gameColor, currentGame);
    displayData.push_back(gameValue);
    
    // Draw Graphics section
    Color graphicsColor = (currentSection == GRAPHICS) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject graphicsTitle(menuItemLeftMargin, 15, 10, 1, ObjectType::TEXT, graphicsColor, "GRAPHICS:");
    displayData.push_back(graphicsTitle);
    
    std::string currentDisplay = libraryManager->getCurrentDisplayName();
    DisplayObject graphicsValue(menuItemRightMargin, 15, currentDisplay.length(), 1, ObjectType::TEXT, graphicsColor, currentDisplay);
    displayData.push_back(graphicsValue);
    
    // Draw Name Input section
    Color nameColor = (currentSection == NAME_INPUT) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject nameTitle(menuItemLeftMargin, 20, 10, 1, ObjectType::TEXT, nameColor, "NAME:");
    displayData.push_back(nameTitle);
    
    DisplayObject nameValue(menuItemRightMargin, 20, playerName.length(), 1, ObjectType::TEXT, nameColor, playerName);
    displayData.push_back(nameValue);
    
    // Instructions
    DisplayObject instructions(menuItemLeftMargin, 25, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "UP/DOWN: Select section, LEFT/RIGHT: Change option");
    displayData.push_back(instructions);
    DisplayObject instructions2(menuItemLeftMargin, 27, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "ENTER: Start with selected options");
    displayData.push_back(instructions2);
    
    return displayData;
}

const std::vector<DisplayObject> MenuManager::getPauseMenuDisplayData() const
{
    std::vector<DisplayObject> displayData;

    // Semi-transparent background
    DisplayObject background(0, 0, _width, _height, ObjectType::RECTANGLE, Color(0, 0, 0, 128), " ");
    displayData.push_back(background);
    
    // Draw borders of pause menu window
    int windowWidth = 40;
    int windowHeight = 20;
    int startX = (_width - windowWidth) / 2;
    int startY = (_height - windowHeight) / 2;
    
    for (int x = 0; x < windowWidth; ++x) {
        DisplayObject topWall(startX + x, startY, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "-");
        displayData.push_back(topWall);

        DisplayObject bottomWall(startX + x, startY + windowHeight - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "-");
        displayData.push_back(bottomWall);
    }

    for (int y = 0; y < windowHeight; ++y) {
        DisplayObject leftWall(startX, startY + y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "|");
        displayData.push_back(leftWall);

        DisplayObject rightWall(startX + windowWidth - 1, startY + y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "|");
        displayData.push_back(rightWall);
    }
    
    // Draw pause title
    DisplayObject title(startX + windowWidth / 2 - 6, startY + 3, 12, 2, ObjectType::TEXT, Color(255, 255, 0), "GAME PAUSED");
    displayData.push_back(title);
    
    // Draw instructions
    DisplayObject resumeInstr(startX + 5, startY + 8, 30, 1, ObjectType::TEXT, Color(255, 255, 255), "P: Resume Game");
    displayData.push_back(resumeInstr);
    
    DisplayObject restartInstr(startX + 5, startY + 10, 30, 1, ObjectType::TEXT, Color(255, 255, 255), "R: Restart Game");
    displayData.push_back(restartInstr);
    
    DisplayObject menuInstr(startX + 5, startY + 12, 30, 1, ObjectType::TEXT, Color(255, 255, 255), "ESC: Return to Main Menu");
    displayData.push_back(menuInstr);
    
    DisplayObject quitInstr(startX + 5, startY + 14, 30, 1, ObjectType::TEXT, Color(255, 255, 255), "Q: Quit Arcade");
    displayData.push_back(quitInstr);
    
    return displayData;
}
