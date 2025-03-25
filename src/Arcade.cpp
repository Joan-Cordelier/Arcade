/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** Arcade
*/

#include "Arcade.hpp"

Arcade::Arcade(std::string lib)
{
    SetCurrentGraph(lib);
    SetCurrentGame("./arcade_menu.so");
    ChargeLibGame();
    ChargeLibGraphique();
}

Arcade::~Arcade()
{
    delete _game;
    delete _display;
}


void Arcade::RunGame()
{
    
}

void Arcade::VerifType()
{
    
}

bool Arcade::ChargeLibGame()
{
    void* handle = dlopen(_currentGame, RTLD_LAZY);
    if (!handle) {
        std::invalid_argument("ERROR: dlopen");
        return false;
    }
    typedef IGame* (*CreateFunct)();
    CreateFunct createGame = (CreateFunct)dlsym(handle, "create");
    if (!createGame) {
        std::invalid_argument("ERROR: create");
        dlclose(handle);
        return false;
    }
    IGame* objet = createGame();
    _game = objet;
    dlclose(handle);
    return true;
}

bool Arcade::ChargeLibGraphique()
{
    void* handle = dlopen(_currentGraph, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Erreur lors du chargement de la bibliothèque : " << dlerror() << std::endl;
        return false;
    }
    typedef IDisplay* (*CreateFunct)();
    CreateFunct create = (CreateFunct)dlsym(handle, "create");
    if (!create) {
        std::cerr << "Erreur lors de la récupération de la fonction : " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }
    IDisplay* objet = create();
    _display = objet;
    dlclose(handle);
    return true;
}

void Arcade::SetCurrentGraph(std::string type)
{
    if (type == "arcade_ncurses.so" || type == "./arcade_ncurses.so"){
        _currentGraph_enum = NCURSE;
        _currentGraph = "./arcade_ncurses.so";
    } else if (type == "arcade_sdl2.so" || type == "./arcade_sdl2.so") {
        _currentGraph_enum = SDL2;
        _currentGraph = "./arcade_sdl2.so";
    } else
        std::invalid_argument("ERROR: bad lib.so");
}

void Arcade::SetCurrentGraph(Graphique type)
{
    if (type == NCURSE){
        _currentGraph_enum = NCURSE;
        _currentGraph = "./arcade_ncurses.so";
    } else if (type == SDL2) {
        _currentGraph_enum = SDL2;
        _currentGraph = "./arcade_sdl2.so";
    } else
        std::invalid_argument("ERROR: bad lib.so");
}

void Arcade::SetCurrentGame(std::string game)
{
    if (game == "arcade_menu.so" || game == "./arcade_menu.so"){
        _currentGame_enum = MENU;
        _currentGame = "./arcade_menu.so";
    } else
        std::invalid_argument("ERROR: bad lib.so");
}

void Arcade::SetCurrentGame(Game game)
{
    if (game == MENU){
        _currentGame_enum = MENU;
        _currentGame = "./arcade_menu.so";
    } else
        std::invalid_argument("ERROR: bad lib.so");
}

Graphique Arcade::GetCurrentGraph()
{
    return _currentGraph_enum;
}

Game Arcade::GetCurrentGame()
{
    return _currentGame_enum;
}
