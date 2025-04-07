/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurse.cpp
*/

#include <iostream>
#include "NCurse.hpp"

NcurseDisplayer::NcurseDisplayer()
{
}

NcurseDisplayer::~NcurseDisplayer()
{

}

void NcurseDisplayer::init(int width, int height)
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);  // TODO: maybe add a cursor for certain modes
    start_color();
    
    if (!has_colors()) {
        endwin();
        std::cerr << "Terminal does not support colors" << std::endl;
        return;
    }
    
    // Use screen size rather than passed dimensions for better compatibility
    _width = COLS;
    _height = LINES;
    
    // Create a window that fills the entire screen
    _window = newwin(_height, _width, 0, 0);
    if (!_window) {
        endwin();
        std::cerr << "Failed to create ncurses window" << std::endl;
        return;
    }
    
    keypad(_window, TRUE);
    
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    
    nodelay(_window, TRUE);
    
    box(_window, 0, 0);
    wrefresh(_window);
    
    _running = true;
}

void NcurseDisplayer::stop()
{
    _running = false;
    if (_window) {
        delwin(_window);
        _window = nullptr;
    }
    endwin();
}

Event NcurseDisplayer::pollEvent()
{
    nodelay(stdscr, TRUE);
    int key = getch();
    nodelay(stdscr, FALSE);
    
    if (key == ERR) {
        return {
            EventType::NONE,
            Key::NONE,
            {-1, -1, -1}
        };
    }
    
    switch (key) {
        case KEY_UP:
            return {
                EventType::KEY_PRESSED,
                Key::UP,
                {-1, -1, -1}
            };
        case KEY_DOWN:
            return {
                EventType::KEY_PRESSED,
                Key::DOWN,
                {-1, -1, -1}
            };
        case KEY_LEFT:
            return {
                EventType::KEY_PRESSED,
                Key::LEFT,
                {-1, -1, -1}
            };
        case KEY_RIGHT:
            return {
                EventType::KEY_PRESSED,
                Key::RIGHT,
                {-1, -1, -1}
            };
        case KEY_ENTER:
        case 10:
            return {
                EventType::KEY_PRESSED,
                Key::ENTER,
                {-1, -1, -1}
            };
        case 27:
            return {
                EventType::KEY_PRESSED,
                Key::ESCAPE,
                {-1, -1, -1}
            };
        case KEY_BACKSPACE:
        case 127:
            return {
                EventType::KEY_PRESSED,
                Key::BACKSPACE,
                {-1, -1, -1}
            };
        case KEY_F(1):
            return {
                EventType::KEY_PRESSED,
                Key::F1,
                {-1, -1, -1}
            };
        case KEY_F(2):
            return {
                EventType::KEY_PRESSED,
                Key::F2,
                {-1, -1, -1}
            };
        case KEY_F(3):
            return {
                EventType::KEY_PRESSED,
                Key::F3,
                {-1, -1, -1}
            };
        case KEY_F(4):
            return {
                EventType::KEY_PRESSED,
                Key::F4,
                {-1, -1, -1}
            };
        case KEY_F(5):
            return {
                EventType::KEY_PRESSED,
                Key::F5,
                {-1, -1, -1}
            };
        case KEY_F(6):
            return {
                EventType::KEY_PRESSED,
                Key::F6,
                {-1, -1, -1}
            };
        case KEY_F(7):
            return {
                EventType::KEY_PRESSED,
                Key::F7,
                {-1, -1, -1}
            };
        case KEY_F(8):
            return {
                EventType::KEY_PRESSED,
                Key::F8,
                {-1, -1, -1}
            };
        case KEY_F(9):
            return {
                EventType::KEY_PRESSED,
                Key::F9,
                {-1, -1, -1}
            };
        case KEY_F(10):
            return {
                EventType::KEY_PRESSED,
                Key::F10,
                {-1, -1, -1}
            };
        case KEY_F(11):
            return {
                EventType::KEY_PRESSED,
                Key::F11,
                {-1, -1, -1}
            };
        case KEY_F(12):
            return {
                EventType::KEY_PRESSED,
                Key::F12,
                {-1, -1, -1}
            };
        case 'a':
        case 'A':
            return {
                EventType::KEY_PRESSED,
                Key::A,
                {-1, -1, -1}
            };
        case 'b':
        case 'B':
            return {
                EventType::KEY_PRESSED,
                Key::B,
                {-1, -1, -1}
            };
        case 'c':
        case 'C':
            return {
                EventType::KEY_PRESSED,
                Key::C,
                {-1, -1, -1}
            };
        case 'd':
        case 'D':
            return {
                EventType::KEY_PRESSED,
                Key::D,
                {-1, -1, -1}
            };
        case 'e':
        case 'E':
            return {
                EventType::KEY_PRESSED,
                Key::E,
                {-1, -1, -1}
            };
        case 'f':
        case 'F':
            return {
                EventType::KEY_PRESSED,
                Key::F,
                {-1, -1, -1}
            };
        case 'g':
        case 'G':
            return {
                EventType::KEY_PRESSED,
                Key::G,
                {-1, -1, -1}
            };
        case 'h':
        case 'H':
            return {
                EventType::KEY_PRESSED,
                Key::H,
                {-1, -1, -1}
            };
        case 'i':
        case 'I':
            return {
                EventType::KEY_PRESSED,
                Key::I,
                {-1, -1, -1}
            };
        case 'j':
        case 'J':
            return {
                EventType::KEY_PRESSED,
                Key::J,
                {-1, -1, -1}
            };
        case 'k':
        case 'K':
            return {
                EventType::KEY_PRESSED,
                Key::K,
                {-1, -1, -1}
            };
        case 'l':
        case 'L':
            return {
                EventType::KEY_PRESSED,
                Key::L,
                {-1, -1, -1}
            };
        case 'm':
        case 'M':
            return {
                EventType::KEY_PRESSED,
                Key::M,
                {-1, -1, -1}
            };
        case 'n':
        case 'N':
            return {
                EventType::KEY_PRESSED,
                Key::N,
                {-1, -1, -1}
            };
        case 'o':
        case 'O':
            return {
                EventType::KEY_PRESSED,
                Key::O,
                {-1, -1, -1}
            };
        case 'p':
        case 'P':
            return {
                EventType::KEY_PRESSED,
                Key::P,
                {-1, -1, -1}
            };
        case 'q':
        case 'Q':
            return {
                EventType::KEY_PRESSED,
                Key::Q,
                {-1, -1, -1}
            };
        case 'r':
        case 'R':
            return {
                EventType::KEY_PRESSED,
                Key::R,
                {-1, -1, -1}
            };
        case 's':
        case 'S':
            return {
                EventType::KEY_PRESSED,
                Key::S,
                {-1, -1, -1}
            };
        case 't':
        case 'T':
            return {
                EventType::KEY_PRESSED,
                Key::T,
                {-1, -1, -1}
            };
        case 'u':
        case 'U':
            return {
                EventType::KEY_PRESSED,
                Key::U,
                {-1, -1, -1}
            };
        case 'v':
        case 'V':
            return {
                EventType::KEY_PRESSED,
                Key::V,
                {-1, -1, -1}
            };
        case 'w':
        case 'W':
            return {
                EventType::KEY_PRESSED,
                Key::W,
                {-1, -1, -1}
            };
        case 'x':
        case 'X':
            return {
                EventType::KEY_PRESSED,
                Key::X,
                {-1, -1, -1}
            };
        case 'y':
        case 'Y':
            return {
                EventType::KEY_PRESSED,
                Key::Y,
                {-1, -1, -1}
            };
        case 'z':
        case 'Z':
            return {
                EventType::KEY_PRESSED,
                Key::Z,
                {-1, -1, -1}
            };
        default:
            return {
                EventType::NONE,
                Key::NONE,
                {-1, -1, -1}
            };
    }
}

void NcurseDisplayer::clear()
{
    if (_window) {
        // Use werase instead of wclear to avoid blinking
        werase(_window);
        box(_window, 0, 0); // Redraw border
        // Don't refresh here, let display() handle it
    }
}

int NcurseDisplayer::createColorPair(const Color& color)
{
    for (size_t i = 0; i < _colors.size(); ++i) {
        if (_colors[i].r == color.r &&
            _colors[i].g == color.g &&
            _colors[i].b == color.b) {
            return static_cast<int>(i + 1);
        }
    }

    if (_colors.size() >= 64) {
        return (static_cast<int>(_colors.size()) % 64) + 1;
    }

    int newPair = static_cast<int>(_colors.size()) + 1;
    short colorIndex = newPair + 7;
    
    int r = color.r * 1000 / 255;
    int g = color.g * 1000 / 255;
    int b = color.b * 1000 / 255;

    init_color(colorIndex, r, g, b);
    init_pair(newPair, colorIndex, COLOR_BLACK);
    
    _colors.push_back(color);

    return newPair;
}

void NcurseDisplayer::display(const std::vector<DisplayObject>& objects)
{
    if (!_window) {
        return;
    }
    
    werase(_window);
    box(_window, 0, 0);
    
    if (!objects.empty()) {
        
        for (const auto& obj : objects) {
            int colorPair = createColorPair(obj.getColor());

            wattron(_window, COLOR_PAIR(colorPair));

            if (obj.getType() == ObjectType::TEXT) {
                std::string text = obj.getText();
                if (!text.empty()) {
                    if (obj.getY() >= 0 && obj.getY() < _height && 
                        obj.getX() >= 0 && obj.getX() < _width) {
                        mvwprintw(_window, obj.getY(), obj.getX(), "%s", text.c_str());
                    }
                }
            } else if (obj.getType() == ObjectType::RECTANGLE) {
                for (int i = 0; i < obj.getHeight() && (obj.getY() + i) < _height; ++i) {
                    for (int j = 0; j < obj.getWidth() && (obj.getX() + j) < _width; ++j) {
                        if (obj.getY() + i >= 0 && obj.getX() + j >= 0) {
                            mvwaddch(_window, obj.getY() + i, obj.getX() + j, '#');
                        }
                    }
                }
            } else if (obj.getType() == ObjectType::CIRCLE) {
                int radius = obj.getWidth() / 2;
                int centerX = obj.getX() + radius;
                int centerY = obj.getY() + radius;
                
                int r_squared = radius * radius;
                for (int y = -radius; y <= radius; y++) {
                    if (centerY + y < 0 || centerY + y >= _height) continue;
                    for (int x = -radius; x <= radius; x++) {
                        if (centerX + x < 0 || centerX + x >= _width) continue;
                        if (x*x + y*y <= r_squared) {
                            mvwaddch(_window, centerY + y, centerX + x, 'O');
                        }
                    }
                }
            } else if (obj.getType() == ObjectType::SPRITE || obj.getType() == ObjectType::CUSTOM) {
                for (int i = 0; i < obj.getHeight() && (obj.getY() + i) < _height; ++i) {
                    for (int j = 0; j < obj.getWidth() && (obj.getX() + j) < _width; ++j) {
                        if (obj.getY() + i >= 0 && obj.getX() + j >= 0) {
                            mvwaddch(_window, obj.getY() + i, obj.getX() + j, '#');
                        }
                    }
                }
            }
            wattroff(_window, COLOR_PAIR(colorPair));
        }
    } else {
        mvwprintw(_window, _height/2, _width/2 - 7, "No objects to display");
    }

    wnoutrefresh(_window);
    
    doupdate();
}

extern "C" IDisplay* createDisplay() {
    return new NcurseDisplayer();
}
