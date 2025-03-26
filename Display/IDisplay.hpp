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

    virtual void drawText(int x, int y, const std::string& text) = 0;
};

extern "C" IDisplay* createDisplay();

#endif
