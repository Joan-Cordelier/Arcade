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
        ) : _x(x), _y(y), _width(width), _height(height), 
            _type(type), _color(color), _text(text), _texturePath(texturePath) {}
    
        int getX() const { return _x; }
        int getY() const { return _y; }
        int getWidth() const { return _width; }
        int getHeight() const { return _height; }
        int getScaleX() const { return _scaleX; }
        int getScaleY() const { return _scaleY; }
        ObjectType getType() const { return _type; }
        Color getColor() const { return _color; }
        const std::string& getText() const { return _text; }
        const std::string& getTexturePath() const { return _texturePath; }
    
        void setX(int newX) { _x = newX; }
        void setY(int newY) { _y = newY; }
        void setWidth(int newWidth) { _width = newWidth; }
        void setHeight(int newHeight) { _height = newHeight; }
        void setScaleX(int newScaleX) { _scaleX = newScaleX; }
        void setScaleY(int newScaleY) { _scaleY = newScaleY; }
        void setType(ObjectType newType) { _type = newType; }
        void setColor(const Color& newColor) { _color = newColor; }
        void setText(const std::string& newText) { _text = newText; }
        void setTexturePath(const std::string& newPath) { _texturePath = newPath; }
    
    private:
        int _x;
        int _y;
        int _width;
        int _height;
        int _scaleX;
        int _scaleY;
        ObjectType _type;
        Color _color;
        std::string _text;
        std::string _texturePath;
};

#endif /* !DISPLAYOBJECT_HPP_ */
