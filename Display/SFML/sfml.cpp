#include "sfml.hpp"
#include <iostream>

SfmlDisplay::SfmlDisplay() {}

SfmlDisplay::~SfmlDisplay() {
    stop();
}

void SfmlDisplay::init(int width, int height) {
    if (window.isOpen()) {
        return;
    }
    window.create(sf::VideoMode(width * 32, height * 32), "Arcade - SFML");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("assets/font.ttf")) {
        std::cerr << "Font not found!\n";
    }
}

void SfmlDisplay::stop() {
    if (window.isOpen())
        window.close();
}

Event SfmlDisplay::pollEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return Event::EXIT;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up: return Event::UP;
                case sf::Keyboard::Down: return Event::DOWN;
                case sf::Keyboard::Left: return Event::LEFT;
                case sf::Keyboard::Right: return Event::RIGHT;
                case sf::Keyboard::Enter: return Event::VALIDATE;
                case sf::Keyboard::Escape: return Event::EXIT;
                default: break;
            }
        }
    }
    return Event::NONE;
}

void SfmlDisplay::clear() {
    window.clear();
}

void SfmlDisplay::display(const std::vector<DisplayObject>& objects) {
    for (const auto& obj : objects)
        drawObject(obj);
    window.display();
}

void SfmlDisplay::drawObject(const DisplayObject& obj) {
    if (!obj.isVisible)
        return;

    sf::Vector2f pos(obj.x * 32.0f, obj.y * 32.0f);

    // Cas texte
    if (obj.type == TileType::TEXT || !obj.content.empty()) {
        sf::Text text;
        text.setFont(font);
        text.setString(obj.content);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(obj.color.colorR, obj.color.colorG, obj.color.colorB, obj.color.alpha));
        text.setPosition(pos);
        window.draw(text);
        return;
    }

    // Sprite
    if (!obj.spritePath.empty()) {
        sf::Sprite sprite;
        sprite.setTexture(loadTexture(obj.spritePath));
        sprite.setScale(obj.scaleX, obj.scaleY);
        sprite.setPosition(pos);
        window.draw(sprite);
        return;
    }

    // Rectangle de couleur
    sf::RectangleShape shape(sf::Vector2f(32.0f * obj.scaleX, 32.0f * obj.scaleY));
    shape.setFillColor(sf::Color(obj.color.colorR, obj.color.colorG, obj.color.colorB, obj.color.alpha));
    shape.setPosition(pos);
    window.draw(shape);
}

void SfmlDisplay::drawText(int x, int y, const std::string& text) {
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::White);
    t.setPosition(x * 32, y * 32);
    window.draw(t);
}

sf::Texture& SfmlDisplay::loadTexture(const std::string& path) {
    if (textureCache.find(path) == textureCache.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load: " << path << "\n";
        }
        textureCache[path] = texture;
    }
    return textureCache[path];
}

std::string SfmlDisplay::get_typeLib() 
{
    return "Garph";
}

extern "C" IDisplay* createDisplay() {
    return new SfmlDisplay();
}
