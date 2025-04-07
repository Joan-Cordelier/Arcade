#pragma once

#include "IGame.hpp"
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

class Snake : public IGame {
public:
    Snake();
    ~Snake() override = default;

    void reset() override;
    void update(Event event) override;
    const std::vector<DisplayObject> getDisplayData() const override;
    int getScore() const override;

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

    void move();
    void generateFood();
    bool isCollision(int x, int y) const;
};

extern "C" IGame* createGame();
