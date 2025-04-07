/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IDisplay.hpp
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "Event.hpp"
#include "../include/DisplayObject.hpp"
#include <string>
#include <vector>

class IDisplay {
public:
    virtual ~IDisplay() = default;

    virtual void init(int width, int height) = 0;
    virtual void stop() = 0;

    virtual Event pollEvent() = 0;

    virtual void clear() = 0;
    virtual void display(const std::vector<DisplayObject>& objects) = 0;
};

extern "C" IDisplay* createDisplay();

#endif
