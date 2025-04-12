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
                case sf::Keyboard::BackSpace: return {EventType::KEY_PRESSED, Key::BACKSPACE, {-1, -1, -1}};
                case sf::Keyboard::F1: return {EventType::KEY_PRESSED, Key::F1, {-1, -1, -1}};
                case sf::Keyboard::F2: return {EventType::KEY_PRESSED, Key::F2, {-1, -1, -1}};
                case sf::Keyboard::F3: return {EventType::KEY_PRESSED, Key::F3, {-1, -1, -1}};
                case sf::Keyboard::F4: return {EventType::KEY_PRESSED, Key::F4, {-1, -1, -1}};
                case sf::Keyboard::F5: return {EventType::KEY_PRESSED, Key::F5, {-1, -1, -1}};
                case sf::Keyboard::F6: return {EventType::KEY_PRESSED, Key::F6, {-1, -1, -1}};
                case sf::Keyboard::F7: return {EventType::KEY_PRESSED, Key::F7, {-1, -1, -1}};
                case sf::Keyboard::F8: return {EventType::KEY_PRESSED, Key::F8, {-1, -1, -1}};
                case sf::Keyboard::F9: return {EventType::KEY_PRESSED, Key::F9, {-1, -1, -1}};
                case sf::Keyboard::F10: return {EventType::KEY_PRESSED, Key::F10, {-1, -1, -1}};
                case sf::Keyboard::F11: return {EventType::KEY_PRESSED, Key::F11, {-1, -1, -1}};
                case sf::Keyboard::F12: return {EventType::KEY_PRESSED, Key::F12, {-1, -1, -1}};
                case sf::Keyboard::A: return {EventType::KEY_PRESSED, Key::A, {-1, -1, -1}};
                case sf::Keyboard::B: return {EventType::KEY_PRESSED, Key::B, {-1, -1, -1}};
                case sf::Keyboard::C: return {EventType::KEY_PRESSED, Key::C, {-1, -1, -1}};
                case sf::Keyboard::D: return {EventType::KEY_PRESSED, Key::D, {-1, -1, -1}};
                case sf::Keyboard::E: return {EventType::KEY_PRESSED, Key::E, {-1, -1, -1}};
                case sf::Keyboard::F: return {EventType::KEY_PRESSED, Key::F, {-1, -1, -1}};
                case sf::Keyboard::G: return {EventType::KEY_PRESSED, Key::G, {-1, -1, -1}};
                case sf::Keyboard::H: return {EventType::KEY_PRESSED, Key::H, {-1, -1, -1}};
                case sf::Keyboard::I: return {EventType::KEY_PRESSED, Key::I, {-1, -1, -1}};
                case sf::Keyboard::J: return {EventType::KEY_PRESSED, Key::J, {-1, -1, -1}};
                case sf::Keyboard::K: return {EventType::KEY_PRESSED, Key::K, {-1, -1, -1}};
                case sf::Keyboard::L: return {EventType::KEY_PRESSED, Key::L, {-1, -1, -1}};
                case sf::Keyboard::M: return {EventType::KEY_PRESSED, Key::M, {-1, -1, -1}};
                case sf::Keyboard::N: return {EventType::KEY_PRESSED, Key::N, {-1, -1, -1}};
                case sf::Keyboard::O: return {EventType::KEY_PRESSED, Key::O, {-1, -1, -1}};
                case sf::Keyboard::P: return {EventType::KEY_PRESSED, Key::P, {-1, -1, -1}};
                case sf::Keyboard::Q: return {EventType::KEY_PRESSED, Key::Q, {-1, -1, -1}};
                case sf::Keyboard::R: return {EventType::KEY_PRESSED, Key::R, {-1, -1, -1}};
                case sf::Keyboard::S: return {EventType::KEY_PRESSED, Key::S, {-1, -1, -1}};
                case sf::Keyboard::T: return {EventType::KEY_PRESSED, Key::T, {-1, -1, -1}};
                case sf::Keyboard::U: return {EventType::KEY_PRESSED, Key::U, {-1, -1, -1}};
                case sf::Keyboard::V: return {EventType::KEY_PRESSED, Key::V, {-1, -1, -1}};
                case sf::Keyboard::W: return {EventType::KEY_PRESSED, Key::W, {-1, -1, -1}};
                case sf::Keyboard::X: return {EventType::KEY_PRESSED, Key::X, {-1, -1, -1}};
                case sf::Keyboard::Y: return {EventType::KEY_PRESSED, Key::Y, {-1, -1, -1}};
                case sf::Keyboard::Z: return {EventType::KEY_PRESSED, Key::Z, {-1, -1, -1}};
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