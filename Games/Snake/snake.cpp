#include "snake.hpp"

Snake::Snake() {
    _inMenu = true;
    _width = 30;
    _height = 20;
    std::srand(std::time(nullptr));
    reset();
}

void Snake::reset() {
    _inMenu = true;
    _snake.clear();
    int startX = _width / 2;
    int startY = _height / 2;

    _snake.push_back({startX, startY});
    _snake.push_back({startX - 1, startY});
    _snake.push_back({startX - 3, startY});    
    
    _dir = RIGHT;
    _score = 0;
    _gameOver = false;
    generateFood();
    _lastMoveTime = std::chrono::steady_clock::now();
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

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMoveTime).count();

    if (elapsed >= _moveDelay) {
        move();
        _lastMoveTime = now;
    }
}

void Snake::move() {
    auto head = _snake.front();
    switch (_dir) {
        case UP:    head.second--; break;
        case DOWN:  head.second++; break;
        case LEFT:  head.first--; break;
        case RIGHT: head.first++; break;
    }

    if (head.first < 1 || head.first >= _width - 1 ||
        head.second < 1 || head.second >= _height - 1 ||
        isCollision(head.first, head.second)) {
        _gameOver = true;
        return;
    }

    _snake.insert(_snake.begin(), head);

    if (head == _food) {
        _score++;
        generateFood();
    } else {
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

bool Snake::isWall(int x, int y) const {
    return x == 0 || x == _width - 1 || y == 0 || y == _height - 1;
}

void Snake::generateFood() {
    int x;
    int y;
    do {
        x = std::rand() % (_width - 2);
        y = std::rand() % (_height - 2);
    } while (isCollision(x, y) || isWall(x, y));
    _food = {x, y};
}

const std::vector<DisplayObject> Snake::getDisplayData() const {
    std::vector<DisplayObject> data;

    const int TILE_SIZE = 32;
    const float SCALE = TILE_SIZE / 32.0f;

    // Bordures (haut et bas)
    for (int x = 0; x < _width; ++x) {
        DisplayObject topWall(x, 0, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        topWall.setScaleX(SCALE);
        topWall.setScaleY(SCALE);
        data.push_back(topWall);

        DisplayObject bottomWall(x, _height - 1, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        bottomWall.setScaleX(SCALE);
        bottomWall.setScaleY(SCALE);
        data.push_back(bottomWall);
    }

    // Bordures (gauche et droite)
    for (int y = 0; y < _height; ++y) {
        DisplayObject leftWall(0, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        leftWall.setScaleX(SCALE);
        leftWall.setScaleY(SCALE);
        data.push_back(leftWall);

        DisplayObject rightWall(_width - 1, y, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 255), "#");
        rightWall.setScaleX(SCALE);
        rightWall.setScaleY(SCALE);
        data.push_back(rightWall);
    }

    // Serpent
    for (size_t i = 0; i < _snake.size(); ++i) {
        const auto& part = _snake[i];
        if (i == 0) {
            DisplayObject head(part.first, part.second, 1, 1, ObjectType::RECTANGLE, Color(255, 255, 0), "O");
            head.setScaleX(SCALE);
            head.setScaleY(SCALE);
            data.push_back(head);
        } else {
            DisplayObject body(part.first, part.second, 1, 1, ObjectType::RECTANGLE, Color(0, 255, 0), "@");
            body.setScaleX(SCALE);
            body.setScaleY(SCALE);
            data.push_back(body);
        }
    }

    // Nourriture
    DisplayObject food(_food.first, _food.second, 1, 1, ObjectType::RECTANGLE, Color(255, 0, 0), "o");
    food.setScaleX(SCALE);
    food.setScaleY(SCALE);
    data.push_back(food);

    // Texte si game over
    if (_gameOver) {
        DisplayObject gameOver(_width / 2 - 5, _height / 2, 10, 1, ObjectType::TEXT, Color(255, 0, 0), "GAME OVER");
        gameOver.setScaleX(1.0f);
        gameOver.setScaleY(1.0f); // Texte généralement non scale
        data.push_back(gameOver);
    }

    return data;
}



int Snake::getScore() const {
    return _score;
}

void Snake::stop()
{
}

extern "C" IGame *createGame()
{
    return new Snake();
}
