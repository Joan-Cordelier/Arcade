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
        case SCORES:
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

    int borderWidth = _width;
    int borderHeight = _height;
    
    // Draw top and bottom borders
    for (int x = 0; x < borderWidth; ++x) {
        DisplayObject topWall(x, 0, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "-");
        displayData.push_back(topWall);

        DisplayObject bottomWall(x, borderHeight - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "-");
        displayData.push_back(bottomWall);
    }

    // Draw left and right borders
    for (int y = 0; y < borderHeight; ++y) {
        DisplayObject leftWall(0, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "|");
        displayData.push_back(leftWall);

        DisplayObject rightWall(borderWidth - 1, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "|");
        displayData.push_back(rightWall);
    }
    
    int menuCenterX = borderWidth / 2;
    int menuItemLeftMargin = 5;
    int menuItemRightMargin = menuItemLeftMargin + 15;
    
    // Draw menu title
    std::string titleText = "ARCADE MENU";
    DisplayObject title(menuCenterX - titleText.length()/2, 5, titleText.length(), 2, ObjectType::TEXT, Color(255, 255, 0), titleText);
    displayData.push_back(title);
    
    // Draw Games section
    Color gameColor = (currentSection == GAMES) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject gamesTitle(menuItemLeftMargin, 8, 10, 1, ObjectType::TEXT, gameColor, "GAMES:");
    displayData.push_back(gamesTitle);
    
    std::string currentGame = libraryManager->getCurrentGameName();
    DisplayObject gameValue(menuItemRightMargin, 8, currentGame.length(), 1, ObjectType::TEXT, gameColor, currentGame);
    displayData.push_back(gameValue);
    
    // Draw Graphics section
    Color graphicsColor = (currentSection == GRAPHICS) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject graphicsTitle(menuItemLeftMargin, 12, 10, 1, ObjectType::TEXT, graphicsColor, "GRAPHICS:");
    displayData.push_back(graphicsTitle);
    
    std::string currentDisplay = libraryManager->getCurrentDisplayName();
    DisplayObject graphicsValue(menuItemRightMargin, 12, currentDisplay.length(), 1, ObjectType::TEXT, graphicsColor, currentDisplay);
    displayData.push_back(graphicsValue);
    
    // Draw Scores section
    Color scoresColor = (currentSection == SCORES) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject scoresTitle(menuItemLeftMargin, 16, 10, 1, ObjectType::TEXT, scoresColor, "SCORES:");
    displayData.push_back(scoresTitle);
    
    // Add score items
    if (currentSection == SCORES) {
        std::vector<DisplayObject> scoreObjects = getScoreDisplay(menuItemRightMargin, 16);
        displayData.insert(displayData.end(), scoreObjects.begin(), scoreObjects.end());
    } else {
        std::string currentGame = libraryManager->getCurrentGameName();
        if (!currentGame.empty()) {
            DisplayObject viewScoresPrompt(menuItemRightMargin, 16, 25, 1, ObjectType::TEXT, scoresColor, "<Select to view scores>");
            displayData.push_back(viewScoresPrompt);
        }
    }
    
    // Draw Name Input section
    Color nameColor = (currentSection == NAME_INPUT) ? Color(0, 255, 0) : Color(255, 255, 255);
    DisplayObject nameTitle(menuItemLeftMargin, 24, 10, 1, ObjectType::TEXT, nameColor, "NAME:");
    displayData.push_back(nameTitle);
    
    DisplayObject nameValue(menuItemRightMargin, 24, playerName.length(), 1, ObjectType::TEXT, nameColor, playerName);
    displayData.push_back(nameValue);
    
    // Instructions
    DisplayObject instructions(menuItemLeftMargin, 26, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "UP/DOWN: Select section, LEFT/RIGHT: Change option");
    displayData.push_back(instructions);
    DisplayObject instructions2(menuItemLeftMargin, 28, 40, 1, ObjectType::TEXT, Color(150, 150, 150), "ENTER: Start with selected options");
    displayData.push_back(instructions2);
    
    return displayData;
}

std::vector<DisplayObject> MenuManager::getScoreDisplay(int startX, int startY) const 
{
    std::vector<DisplayObject> scoreObjects;
    
    std::string currentGame = libraryManager->getCurrentGameName();
    if (currentGame.empty()) return scoreObjects;
    
    auto formattedScores = scoreManager->getFormattedScores(currentGame);
    
    // Display the game name as header
    DisplayObject gameHeader(startX, startY, currentGame.length(), 1, ObjectType::TEXT, Color(255, 255, 0), currentGame);
    scoreObjects.push_back(gameHeader);
    
    // Display top scores
    int yOffset = 2;
    if (formattedScores.empty()) {
        DisplayObject noScores(startX, startY + yOffset, 15, 1, ObjectType::TEXT, Color(255, 255, 255), "No scores yet");
        scoreObjects.push_back(noScores);
    } else {
        // Headers
        DisplayObject rankHeader(startX, startY + yOffset, 5, 1, ObjectType::TEXT, Color(200, 200, 200), "Rank");
        DisplayObject nameHeader(startX + 6, startY + yOffset, 10, 1, ObjectType::TEXT, Color(200, 200, 200), "Player");
        DisplayObject scoreHeader(startX + 20, startY + yOffset, 10, 1, ObjectType::TEXT, Color(200, 200, 200), "Score");
        
        scoreObjects.push_back(rankHeader);
        scoreObjects.push_back(nameHeader);
        scoreObjects.push_back(scoreHeader);
        
        // Display up to 5 scores
        int limit = std::min(5, static_cast<int>(formattedScores.size()));
        for (int i = 0; i < limit; i++) {
            yOffset += 1;
            
            // Rank number
            std::string rankStr = std::to_string(i + 1) + ".";
            DisplayObject rank(startX, startY + yOffset, rankStr.length(), 1, ObjectType::TEXT, Color(255, 255, 255), rankStr);
            
            // Player name (truncate if necessary)
            std::string playerNameStr = formattedScores[i].first;
            if (playerNameStr.length() > 12) {
                playerNameStr = playerNameStr.substr(0, 9) + "...";
            }
            DisplayObject name(startX + 6, startY + yOffset, playerNameStr.length(), 1, ObjectType::TEXT, Color(255, 255, 255), playerNameStr);
            
            // Score
            std::string scoreStr = std::to_string(formattedScores[i].second);
            DisplayObject score(startX + 20, startY + yOffset, scoreStr.length(), 1, ObjectType::TEXT, Color(255, 255, 255), scoreStr);
            
            scoreObjects.push_back(rank);
            scoreObjects.push_back(name);
            scoreObjects.push_back(score);
        }
    }
    
    return scoreObjects;
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
