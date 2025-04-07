/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** LibraryManager.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <dlfcn.h>
#include "../Display/IDisplay.hpp"
#include "../Games/IGame.hpp"

class LibraryManager {
    public:
        LibraryManager();
        ~LibraryManager();

        // Parssing
        std::vector<std::string> findLibraries(const std::string& prefix) const;
        bool isDisplayLibrary(const std::string& path) const;
        bool isGameLibrary(const std::string& path) const;

        IDisplay* loadDisplayLibrary(const std::string& path);
        IGame* loadGameLibrary(const std::string& path);

        void closeDisplayLibrary();
        void closeGameLibrary();

        IDisplay* nextDisplay();
        IGame* nextGame();

        const std::vector<std::string>& getDisplayLibs() const { return displayLibs; }
        const std::vector<std::string>& getGameLibs() const { return gameLibs; }
        int getCurrentDisplayIndex() const { return currentDisplayIndex; }
        int getCurrentGameIndex() const { return currentGameIndex; }

    private:
        void loadLibrary(void** handle, const std::string& path);
        void closeLibrary(void* handle);
        void refreshLibraryLists();

        std::vector<std::string> displayLibs;
        std::vector<std::string> gameLibs;

        int currentDisplayIndex;
        int currentGameIndex;

        std::string currentDisplayPath;
        std::string currentGamePath;

        void* displayHandle;
        void* gameHandle;

        IDisplay* display;
        IGame* game;
};
