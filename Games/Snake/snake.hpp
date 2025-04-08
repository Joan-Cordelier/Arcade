#pragma once

#include "../IGame.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <chrono>

class Snake : public IGame {
public:
    Snake();
    ~Snake() override = default;

    void reset() override;
    void update(Event event) override;
    const std::vector<DisplayObject> getDisplayData() const override;
    int getScore() const override;
    void stop() override;
    bool isWall(int x, int y) const;

private:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    std::vector<std::pair<int, int>> _snake;  // Positions du serpent
    std::pair<int, int> _food;                // Position de la nourriture
    Direction _dir;
    std::vector<DisplayObject> _object;
    int _score;
    int _width;
    int _height;
    bool _gameOver;
    std::chrono::steady_clock::time_point _lastMoveTime;
    const int _moveDelay = 150;

    bool _inMenu = true;

    void move();
    void generateFood();
    bool isCollision(int x, int y) const;
};

extern "C" IGame* createGame();
