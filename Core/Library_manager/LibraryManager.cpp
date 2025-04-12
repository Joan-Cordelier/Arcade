/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** LibraryManager.cpp
*/

#include "../Library_manager/LibraryManager.hpp"
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <algorithm>

LibraryManager::LibraryManager() 
    : currentDisplayIndex(0), currentGameIndex(0), 
      displayHandle(nullptr), gameHandle(nullptr), 
      display(nullptr), game(nullptr)
{
    refreshLibraryLists();
}

LibraryManager::~LibraryManager()
{
    closeDisplayLibrary();
    closeGameLibrary();
}

void LibraryManager::refreshLibraryLists()
{
    std::vector<std::string> allLibs = findLibraries("arcade_");
    
    displayLibs.clear();
    gameLibs.clear();
    
    for (const auto& lib : allLibs) {
        if (isDisplayLibrary(lib)) {
            displayLibs.push_back(lib);
        } else if (isGameLibrary(lib)) {
            gameLibs.push_back(lib);
        }
    }
    
    // Sort libraries alphabetically
    std::sort(displayLibs.begin(), displayLibs.end());
    std::sort(gameLibs.begin(), gameLibs.end());
}

std::vector<std::string> LibraryManager::findLibraries(const std::string& prefix) const
{
    std::vector<std::string> libraries;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator("./lib")) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.find(prefix) == 0 && filename.rfind(".so") == filename.length() - 3) {
                    libraries.push_back("./lib/" + filename);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error scanning library directory: " << e.what() << std::endl;
    }
    
    return libraries;
}

bool LibraryManager::isDisplayLibrary(const std::string& path) const
{
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        return false;
    }
    
    void* sym = dlsym(handle, "createDisplay");
    bool result = (sym != nullptr);
    dlclose(handle);
    
    return result;
}

bool LibraryManager::isGameLibrary(const std::string& path) const
{
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        return false;
    }
    
    void* sym = dlsym(handle, "createGame");
    bool result = (sym != nullptr);
    dlclose(handle);
    
    return result;
}

IDisplay* LibraryManager::loadDisplayLibrary(const std::string& path)
{
    closeDisplayLibrary();
    
    try {
        loadLibrary(&displayHandle, path);
        
        using CreateDisplayFunc = IDisplay* (*)();
        CreateDisplayFunc createDisplay = reinterpret_cast<CreateDisplayFunc>(dlsym(displayHandle, "createDisplay"));
        
        if (createDisplay == nullptr) {
            std::string error = dlerror();
            closeLibrary(displayHandle);
            displayHandle = nullptr;
            throw std::runtime_error("Invalid display library: " + error);
        }
        
        display = createDisplay();
        if (display == nullptr) {
            closeLibrary(displayHandle);
            displayHandle = nullptr;
            throw std::runtime_error("Failed to create display instance");
        }
        
        currentDisplayPath = path;
        
        for (size_t i = 0; i < displayLibs.size(); ++i) {
            if (displayLibs[i] == path) {
                currentDisplayIndex = i;
                break;
            }
        }
        
        return display;
    } catch (const std::exception& e) {
        if (displayHandle != nullptr) {
            closeLibrary(displayHandle);
            displayHandle = nullptr;
        }
        display = nullptr;
        std::cerr << "Error loading display library: " << e.what() << std::endl;
        throw;
    }
}

IGame* LibraryManager::loadGameLibrary(const std::string& path)
{
    closeGameLibrary();
    
    loadLibrary(&gameHandle, path);
    
    using CreateGameFunc = IGame* (*)();
    CreateGameFunc createGame = reinterpret_cast<CreateGameFunc>(dlsym(gameHandle, "createGame"));
    
    if (createGame == nullptr) {
        closeLibrary(gameHandle);
        gameHandle = nullptr;
        throw std::runtime_error("Invalid game library: missing createGame function");
    }
    
    game = createGame();
    if (game == nullptr) {
        closeLibrary(gameHandle);
        gameHandle = nullptr;
        throw std::runtime_error("Failed to create game instance");
    }
    
    currentGamePath = path;
    
    for (size_t i = 0; i < gameLibs.size(); ++i) {
        if (gameLibs[i] == path) {
            currentGameIndex = i;
            break;
        }
    }
    
    return game;
}

void LibraryManager::closeDisplayLibrary()
{
    if (display != nullptr) {
        try {
            display->stop();
            
            usleep(100000);
            
            delete display;
            display = nullptr;
            
            usleep(50000);
        } catch (const std::exception& e) {
            std::cerr << "Error stopping display: " << e.what() << std::endl;
        }
    }
    
    if (displayHandle != nullptr) {
        closeLibrary(displayHandle);
        displayHandle = nullptr;
        
        usleep(50000);
    }
}

void LibraryManager::closeGameLibrary()
{
    if (game != nullptr) {
        try {
            game->stop();
        } catch (const std::exception& e) {
            std::cerr << "Error stopping game: " << e.what() << std::endl;
        }
        delete game;
        game = nullptr;
    }
    
    if (gameHandle != nullptr) {
        closeLibrary(gameHandle);
        gameHandle = nullptr;
    }
}

IDisplay* LibraryManager::nextDisplay()
{
    if (displayLibs.empty())
        throw std::runtime_error("No display libraries available");
    
    currentDisplayIndex = (currentDisplayIndex + 1) % displayLibs.size();

    usleep(200000);
        
    return loadDisplayLibrary(displayLibs[currentDisplayIndex]);
}

IGame* LibraryManager::nextGame()
{
    if (gameLibs.empty())
        throw std::runtime_error("No game libraries available");
    
    currentGameIndex = (currentGameIndex + 1) % gameLibs.size();
    return loadGameLibrary(gameLibs[currentGameIndex]);
}

void LibraryManager::loadLibrary(void** handle, const std::string& path)
{
    *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (*handle == nullptr) {
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
    }
}

void LibraryManager::closeLibrary(void* handle)
{
    if (handle != nullptr) {
        dlclose(handle);
    }
}
