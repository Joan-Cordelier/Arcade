/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2.cpp
*/

#include "SDL2.hpp"

SDL2::SDL2() {
}

SDL2::~SDL2() {
    SDL_Quit();
}


void SDL2::init(int width, int height) 
{
}

void SDL2::stop() 
{
}

Event SDL2::pollEvent() 
{
    return Event();
}

void SDL2::clear() 
{
}

void SDL2::display(const std::vector<DisplayObject>& objects) 
{
}

extern "C" IDisplay* create() {
    return new SDL2();
}
