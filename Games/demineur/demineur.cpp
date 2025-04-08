#include "demineur.hpp"
#include <random>
#include <iostream>
#include <ctime>

Demineur::Demineur() {
    std::srand(std::time(nullptr));
    _inMenu = true;
    _selectedDifficulty = 0;
    _cursor = {0, 0};
    _gameOver = false;
    _won = false;
}

void Demineur::reset() {
    _inMenu = true;
    _selectedDifficulty = 0;
    _cursor = {0, 0};
    _gameOver = false;
    _won = false;
    _board.clear();
}

void Demineur::update(Event event) {
    if (_gameOver || _won)
        return;

    if (_inMenu) {
        if (event.type == EventType::KEY_PRESSED) {
            if (event.key == Key::UP)
                _selectedDifficulty = (_selectedDifficulty + _difficulties.size() - 1) % _difficulties.size();
            else if (event.key == Key::DOWN)
                _selectedDifficulty = (_selectedDifficulty + 1) % _difficulties.size();
            else if (event.key == Key::ENTER)
                initGame(_difficulties[_selectedDifficulty]);
        }
    } else {
        handleInput(event);
    }
}

void Demineur::initGame(int bombs) {
    _inMenu = false;
    _bombCount = bombs;
    _cursor = {0, 0};
    _revealedCount = 0;

    if (bombs <= 20) {
        _width = 10;
        _height = 10;
    } else if (bombs <= 50) {
        _width = 15;
        _height = 15;
    } else {
        _width = 20;
        _height = 20;
    }

    _board = std::vector<Cell>(_width * _height);

    int placed = 0;
    while (placed < _bombCount) {
        int index = std::rand() % (_width * _height);
        if (!_board[index].isBomb) {
            _board[index].isBomb = true;
            placed++;
        }
    }

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            int idx = y * _width + x;
            if (_board[idx].isBomb) continue;
            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || ny < 0 || nx >= _width || ny >= _height) continue;
                    if (_board[ny * _width + nx].isBomb)
                        count++;
                }
            }
            _board[idx].adjacent = count;
        }
    }
}

void Demineur::handleInput(Event event) {
    if (event.type != EventType::KEY_PRESSED)
        return;

    int& x = _cursor.first;
    int& y = _cursor.second;

    if (event.key == Key::UP && y > 0) y--;
    else if (event.key == Key::DOWN && y < _height - 1) y++;
    else if (event.key == Key::LEFT && x > 0) x--;
    else if (event.key == Key::RIGHT && x < _width - 1) x++;
    else if (event.key == Key::F) {
        _board[y * _width + x].isFlagged = !_board[y * _width + x].isFlagged;
    }
    else if (event.key == Key::SPACE) {
        reveal(x, y);
    }
}

void Demineur::reveal(int x, int y) {
    int idx = y * _width + x;
    if (_board[idx].isRevealed || _board[idx].isFlagged)
        return;

    _board[idx].isRevealed = true;
    _revealedCount++;

    if (_board[idx].isBomb) {
        _gameOver = true;
        return;
    }

    // Révélation en cascade
    if (_board[idx].adjacent == 0) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = x + dx;
                int ny = y + dy;
                if (dx == 0 && dy == 0) continue;
                if (nx < 0 || ny < 0 || nx >= _width || ny >= _height) continue;
                reveal(nx, ny);
            }
        }
    }

    // Vérifie la victoire
    if (_revealedCount + _bombCount == _width * _height)
        _won = true;
}

const std::vector<DisplayObject> Demineur::getDisplayData() const {
    std::vector<DisplayObject> data;

    if (_inMenu) {
        data.emplace_back(5, 1, 1, 1, ObjectType::TEXT, Color(255, 255, 255), "== Choix Difficulte ==");

        for (size_t i = 0; i < _difficulties.size(); ++i) {
            std::string label = (_selectedDifficulty == static_cast<int>(i) ? "> " : "  ");
            label += std::to_string(_difficulties[i]) + " bombes";
            data.emplace_back(5, 3 + i, 1, 1, ObjectType::TEXT, Color(0, 255, 0), label);
        }
        return data;
    }

    // Affichage du plateau
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            const Cell& cell = _board[y * _width + x];
            std::string content = "#";
            Color color(200, 200, 200);

            if (cell.isRevealed) {
                if (cell.isBomb){
                    content = "*", color = Color(255, 0, 0);
                }
                else if (cell.adjacent > 0) {
                    content = std::to_string(cell.adjacent);
                }
                else {
                    content = ".", color = Color(200, 200, 200);
                }
            } else if (cell.isFlagged) {
                content = "F", color = Color(255, 255, 0);
            }

            if (_cursor.first == x && _cursor.second == y)
                color = Color(0, 255, 255); // curseur visible

            data.emplace_back(x, y, 1, 1, ObjectType::TEXT, color, content);
        }
    }

    if (_gameOver) {
        data.emplace_back(5, _height + 2, 1, 1, ObjectType::TEXT, Color(255, 0, 0), "Game Over!");
    } else if (_won) {
        data.emplace_back(5, _height + 2, 1, 1, ObjectType::TEXT, Color(0, 255, 0), "You Win!");
    }

    return data;
}

int Demineur::getScore() const {
    return _won ? 100 : _score;
}

void Demineur::stop()
{}

extern "C" IGame *createGame()
{
    return new Demineur();
}
