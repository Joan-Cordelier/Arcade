#pragma once

#include "../IGame.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"
#include <vector>
#include <string>
#include <utility>

class minesweeper : public IGame {
public:
    minesweeper();
    ~minesweeper() override = default;

    void reset() override;
    void update(Event event) override;
    const std::vector<DisplayObject> getDisplayData() const override;
    int getScore() const override;
    void stop() override;
    void placeBombs(int safeX, int safeY);

private:
    struct Cell {
        bool isBomb = false;
        bool isRevealed = false;
        bool isFlagged = false;
        int adjacent = 0;
    };

    std::vector<Cell> _board;
    int _width;
    int _height;
    int _bombCount;
    int _revealedCount;
    int _score = 0;
    bool _gameOver = false;
    bool _won = false;
    bool _firstClick = false;

    std::pair<int, int> _cursor;

    // Menu
    bool _inMenu = true;
    std::vector<int> _difficulties = {20, 50, 100};
    int _selectedDifficulty = 0;

    void initGame(int bombs);
    void handleInput(Event event);
    void reveal(int x, int y);
};

extern "C" IGame* createGame();
