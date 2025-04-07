/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** MenuManager.hpp
*/

#pragma once

#include <string>
#include <vector>
#include "../Display/IDisplay.hpp"
#include "../include/DisplayObject.hpp"

enum MenuSection {
    GAMES,
    GRAPHICS,
    NAME_INPUT
};

class LibraryManager;
class ScoreManager;

class MenuManager {
public:
    MenuManager(LibraryManager* libManager, ScoreManager* scoreManager);
    ~MenuManager() = default;

    // Menu state
    bool isInMenu() const { return inMenu; }
    void setMenuState(bool state) { inMenu = state; }

    // Player
    const std::string& getPlayerName() const { return playerName; }
    void setPlayerName(const std::string& name) { playerName = name; }
    void addPlayerNameChar(char c);
    void removePlayerNameChar();

    // Navigation
    void selectPreviousItem();
    void selectNextItem();
    void validateSelection();
    
    // Menu display
    void renderMenu(IDisplay* display, const std::vector<std::string>& displayLibs,
                    const std::vector<std::string>& gameLibs, int currentDisplayIndex,
                    int currentGameIndex);
    
    void handleMenuInput(const Event& event);
    
    // Menu selection info
    MenuSection getCurrentSection() const { return currentSection; }
    int getCurrentSelection() const { return currentSelection; }

    void drawText(IDisplay* display, int x, int y, const std::string& text) {
        display->display({DisplayObject(x, y, 0, 0, ObjectType::TEXT, Color(), text)});
    }

private:
    bool inMenu;
    MenuSection currentSection;
    int currentSelection;
    
    // Player
    std::string playerName;
    
    LibraryManager* libraryManager;
    ScoreManager* scoreManager;
    
    // Display methods (on les changera Mike j'ai fait un peu à l'arrache pour le moment)
    void renderGamesSection(IDisplay* display, const std::vector<std::string>& gameLibs, int currentGameIndex);
    void renderGraphicsSection(IDisplay* display, const std::vector<std::string>& displayLibs, int currentDisplayIndex);
    void renderNameSection(IDisplay* display);
    void renderScoresSection(IDisplay* display);
    void renderControlsSection(IDisplay* display);
};