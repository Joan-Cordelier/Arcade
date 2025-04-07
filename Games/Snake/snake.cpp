#include "snake.hpp"

Snake::Snake() {
    _width = 30;
    _height = 20;
    std::srand(std::time(nullptr));
    reset();
}

void Snake::reset() {
    _snake.clear();
    _snake.push_back({_width / 2, _height / 2});
    _dir = RIGHT;
    _score = 0;
    _gameOver = false;
    generateFood();
}

void Snake::update(Event event) {
    if (_gameOver)
        return;

    if (event.key == Key::UP && _dir != DOWN)
        _dir = UP;
    else if (event.key == Key::DOWN && _dir != UP)
        _dir = DOWN;
    else if (event.key == Key::LEFT && _dir != RIGHT)
        _dir = LEFT;
    else if (event.key == Key::RIGHT && _dir != LEFT)
        _dir = RIGHT;

    move();
}

void Snake::move() {
    auto head = _snake.front();
    switch (_dir) {
        case UP:    head.second--;break;
        case DOWN:  head.second++; break;
        case LEFT:  head.first--; break;
        case RIGHT: head.first++; break;
    }

    // Collision avec murs
    if (head.first < 0 || head.first >= _width || head.second < 0 || head.second >= _height || isCollision(head.first, head.second)) {
        _gameOver = true;
        return;
    }

    // Manger la nourriture
    if (head == _food) {
        _snake.insert(_snake.begin(), head);
        _score++;
        generateFood();
    } else {
        _snake.insert(_snake.begin(), head);
        _snake.pop_back();
    }
}

bool Snake::isCollision(int x, int y) const {
    for (const auto& part : _snake) {
        if (part.first == x && part.second == y)
            return true;
    }
    return false;
}

void Snake::generateFood() {
    int x, y;
    do {
        x = std::rand() % _width;
        y = std::rand() % _height;
    } while (isCollision(x, y));
    _food = {x, y};
}

const std::vector<DisplayObject> Snake::getDisplayData() const {
    std::vector<DisplayObject> data;

    // Bordures (haut et bas)
    for (int x = 0; x < _width; ++x) {
        data.push_back(DisplayObject(x, 0, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#"));
        data.push_back(DisplayObject(x, _height - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#"));
    }

    // Bordures (gauche et droite)
    for (int y = 0; y < _height; ++y) {
        data.push_back(DisplayObject(0, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#"));
        data.push_back(DisplayObject(_width - 1, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#"));
    }

    // Serpent
    for (const auto& part : _snake) {
        data.push_back(DisplayObject(part.first, part.second, 1, 1, ObjectType::RECTANGLE, Color(0, 255, 0), "@"));
    }

    // Nourriture
    data.push_back(DisplayObject(_food.first, _food.second, 1, 1, ObjectType::RECTANGLE, Color(255, 0, 0), "o"));

    // Texte si game over
    if (_gameOver) {
        data.push_back(DisplayObject(_width / 2 - 5, _height / 2, 10, 1, ObjectType::TEXT, Color(255, 0, 0), "GAME OVER"));
    }

    return data;
}


int Snake::getScore() const {
    return _score;
}
