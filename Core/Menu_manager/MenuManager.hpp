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
#include "../include/Event.hpp"

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
        void selectNextItem();

        // Menu display
        void update(Event event);
        const std::vector<DisplayObject> getDisplayData() const;

        // Menu selection info
        MenuSection getCurrentSection() const { return currentSection; }
        int getCurrentSelection() const { return currentSelection; }

    private:
        bool inMenu;
        MenuSection currentSection;
        int currentSelection;
        int _width = 80;
        int _height = 40;
        
        // Player
        std::string playerName;
        
        LibraryManager* libraryManager;
        ScoreManager* scoreManager;
};
