/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame.hpp
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "Event.hpp"
#include "DisplayObject.hpp"
#include <vector>

class IGame {
    public:
        virtual ~IGame() = default;
    
        virtual void reset() = 0;
    
        virtual void update(Event event) = 0;
    
        virtual const std::vector<DisplayObject> getDisplayData() const = 0;
    
        virtual int getScore() const = 0;

        virtual void stop() = 0;
};

extern "C" IGame* createGame();

#endif // IGAMEMODULE_HPP_
