/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** DisplayObject.hpp
*/

#ifndef DISPLAYOBJECT_HPP_
#define DISPLAYOBJECT_HPP_

#include <string>

enum class ObjectType {
    RECTANGLE,
    CIRCLE,
    TEXT,
    SPRITE,
    CUSTOM
};

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color(unsigned char red = 255, unsigned char green = 255, 
          unsigned char blue = 255, unsigned char alpha = 255) 
        : r(red), g(green), b(blue), a(alpha) {}
};

class DisplayObject {
    public:
        DisplayObject(
            int x = 0, 
            int y = 0, 
            int width = 0, 
            int height = 0, 
            ObjectType type = ObjectType::RECTANGLE,
            Color color = Color(),
            const std::string& text = "",
            const std::string& texturePath = ""
        ) : x(x), y(y), width(width), height(height), 
            type(type), color(color), text(text), texturePath(texturePath) {}
    
        int getX() const { return x; }
        int getY() const { return y; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        ObjectType getType() const { return type; }
        Color getColor() const { return color; }
        const std::string& getText() const { return text; }
        const std::string& getTexturePath() const { return texturePath; }
    
        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }
        void setWidth(int newWidth) { width = newWidth; }
        void setHeight(int newHeight) { height = newHeight; }
        void setType(ObjectType newType) { type = newType; }
        void setColor(const Color& newColor) { color = newColor; }
        void setText(const std::string& newText) { text = newText; }
        void setTexturePath(const std::string& newPath) { texturePath = newPath; }
    
    private:
        int x;
        int y;
        int width;
        int height;
        ObjectType type;
        Color color;
        std::string text;
        std::string texturePath;
};

#endif /* !DISPLAYOBJECT_HPP_ */
