#pragma once

#include "../IDisplay.hpp"

#include "IDisplay.hpp"
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
    void drawText(int x, int y, const std::string& text) override;
    std::string get_typeLib() override;

private:
    sf::RenderWindow window;
    sf::Font font;
    std::unordered_map<std::string, sf::Texture> textureCache;

    void drawObject(const DisplayObject& obj);
    sf::Texture& loadTexture(const std::string& path);
};

extern "C" IDisplay* createDisplay();
