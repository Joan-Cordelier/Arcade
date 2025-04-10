/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** sfml.cpp
*/

#include "sfml.hpp"
#include <iostream>

SfmlDisplay::SfmlDisplay() {}

SfmlDisplay::~SfmlDisplay() {
    stop();
}

void SfmlDisplay::init(int width, int height) {
    if (window.isOpen()) {
        textureCache.clear();
        window.close();
    }
    
    window.create(sf::VideoMode(width * 32, height * 32), "Arcade - SFML");
    
    if (!window.isOpen()) {
        std::cerr << "Failed to create SFML window!" << std::endl;
        return;
    }
    
    window.setFramerateLimit(60);

    if (!font.loadFromFile("Display/assets/font.ttf")) {
        std::cerr << "Font not found! " << "Display/assets/font.ttf" << std::endl;
    }
}

void SfmlDisplay::stop() {
    if (window.isOpen()) {
        textureCache.clear();
        window.close();
    }
}

Event SfmlDisplay::pollEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return {
                EventType::EXIT,
                Key::NONE,
                {-1, -1, -1}
            };
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up: return {EventType::KEY_PRESSED, Key::UP, {-1, -1, -1}};
                case sf::Keyboard::Down: return {EventType::KEY_PRESSED, Key::DOWN, {-1, -1, -1}};
                case sf::Keyboard::Left: return {EventType::KEY_PRESSED, Key::LEFT, {-1, -1, -1}};
                case sf::Keyboard::Right: return {EventType::KEY_PRESSED, Key::RIGHT, {-1, -1, -1}};
                case sf::Keyboard::Space: return {EventType::KEY_PRESSED, Key::SPACE, {-1, -1, -1}};
                case sf::Keyboard::Enter: return {EventType::KEY_PRESSED, Key::ENTER, {-1, -1, -1}};
                case sf::Keyboard::Escape: return {EventType::KEY_PRESSED, Key::ESCAPE, {-1, -1, -1}};
                case sf::Keyboard::F: return {EventType::KEY_PRESSED, Key::F, {-1, -1, -1}};
                case sf::Keyboard::F1: return {EventType::KEY_PRESSED, Key::F1, {-1, -1, -1}};
                case sf::Keyboard::F2: return {EventType::KEY_PRESSED, Key::F2, {-1, -1, -1}};
                case sf::Keyboard::F3: return {EventType::KEY_PRESSED, Key::F3, {-1, -1, -1}};
                case sf::Keyboard::F4: return {EventType::KEY_PRESSED, Key::F4, {-1, -1, -1}};
                case sf::Keyboard::F5: return {EventType::KEY_PRESSED, Key::F5, {-1, -1, -1}};
                case sf::Keyboard::F6: return {EventType::KEY_PRESSED, Key::F6, {-1, -1, -1}};
                default: break;
            }
        }
    }
    return {
        EventType::NONE,
        Key::NONE,
        {-1, -1, -1}
    };
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

    sf::Vector2f pos(obj.getX() * 32.0f, obj.getY() * 32.0f);

    // Cas texte
    if (obj.getType() == ObjectType::TEXT && !obj.getText().empty()) {
        sf::Text text;
        text.setFont(font);
        text.setString(obj.getText());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(obj.getColor().r, obj.getColor().g, obj.getColor().b, obj.getColor().a));
        text.setPosition(pos);
        window.draw(text);
        return;
    }

    // Sprite
    if (obj.getType() == ObjectType::SPRITE && !obj.getTexturePath().empty()) {
        sf::Sprite sprite;
        sprite.setTexture(loadTexture(obj.getTexturePath()));
        sprite.setScale(obj.getScaleX(), obj.getScaleY());
        sprite.setPosition(pos);
        window.draw(sprite);
        return;
    }

    // Rectangle de couleur
    sf::RectangleShape shape(sf::Vector2f(32.0f * obj.getScaleX(), 32.0f * obj.getScaleY()));
    shape.setFillColor(sf::Color(obj.getColor().r, obj.getColor().g, obj.getColor().b, obj.getColor().a));
    shape.setPosition(pos);
    window.draw(shape);
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

extern "C" IDisplay* createDisplay() {
    return new SfmlDisplay();
}