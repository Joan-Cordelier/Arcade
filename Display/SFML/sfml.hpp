/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** sfml.hpp
*/

#pragma once

#include "../IDisplay.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class SfmlDisplay : public IDisplay {
    public:
        SfmlDisplay();
        ~SfmlDisplay() override;

        void init(int width, int height) override;
        void stop() override;
        Event pollEvent() override;
        void clear() override;
        void display(const std::vector<DisplayObject>& objects) override;
    private:
        sf::RenderWindow window;
        sf::Font font;
        std::unordered_map<std::string, sf::Texture> textureCache;

        void drawObject(const DisplayObject& obj);
        sf::Texture& loadTexture(const std::string& path);
};

extern "C" IDisplay* createDisplay() {
    return new SfmlDisplay();
}
