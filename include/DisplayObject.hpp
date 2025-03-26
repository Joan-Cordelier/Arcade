#ifndef DISPLAYOBJECT_HPP_
#define DISPLAYOBJECT_HPP_

#include <string>

enum class TileType {
    EMPTY,
    WALL,
    PLAYER,
    ENEMY,
    FOOD,
    BACKGROUND,
    TEXT,
    CUSTOM
};

struct DisplayObject {
    int x;
    int y;

    TileType type;

    std::string content = "";

    std::string spritePath = "";

    int colorR = 255;
    int colorG = 255;
    int colorB = 255;

    int alpha = 255;

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    int zIndex = 0;

    int animationId = -1;

    bool isVisible = true;
};

#endif
