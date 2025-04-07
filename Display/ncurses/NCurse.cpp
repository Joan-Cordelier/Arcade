/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurse.cpp
*/

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
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    _running = true;
}

void NcurseDisplayer::stop()
{
    _running = false;
    endwin();
}

Event NcurseDisplayer::pollEvent()
{
    int key = getch();
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
    ::clear();
}

int NcurseDisplayer::createColorPair(const Color& color)
{
    short colorIndex = _colorPairCount + 8;

    int r = color.r * 1000 / 255;
    int g = color.g * 1000 / 255;
    int b = color.b * 1000 / 255;

    init_color(colorIndex, r, g, b);

    init_pair(_colorPairCount + 1, colorIndex, COLOR_BLACK);
    _colorPairCount++;
    
    return _colorPairCount;
}

void NcurseDisplayer::display(const std::vector<DisplayObject>& objects)
{
    for (const auto& obj : objects) {
        int colorPair = createColorPair(obj.getColor());
        if (obj.getType() == ObjectType::RECTANGLE) {
            attron(COLOR_PAIR(static_cast<short>(colorPair)));
            for (int i = 0; i < obj.getHeight(); ++i) {
                mvhline(obj.getY() + i, obj.getX(), ' ', obj.getWidth());
            }
            attroff(COLOR_PAIR(static_cast<short>(colorPair)));
        } else if (obj.getType() == ObjectType::TEXT) {
            attron(COLOR_PAIR(static_cast<short>(colorPair)));
            mvprintw(obj.getY(), obj.getX(), "%s", obj.getText().c_str());
            attroff(COLOR_PAIR(static_cast<short>(colorPair)));
        }
        else if (obj.getType() == ObjectType::SPRITE) {
            //TODO: Handle sprite drawing
            attron(COLOR_PAIR(static_cast<short>(colorPair)));
            for (int i = 0; i < obj.getHeight(); ++i) {
                mvhline(obj.getY() + i, obj.getX(), ' ', obj.getWidth());
            }
            attroff(COLOR_PAIR(static_cast<short>(colorPair)));
        }
        else if (obj.getType() == ObjectType::CUSTOM) {
            //TODO: Handle custom drawing
            attron(COLOR_PAIR(static_cast<short>(colorPair)));
            for (int i = 0; i < obj.getHeight(); ++i) {
                mvhline(obj.getY() + i, obj.getX(), ' ', obj.getWidth());
            }
            attroff(COLOR_PAIR(static_cast<short>(colorPair)));
        }
        else if (obj.getType() == ObjectType::CIRCLE) {
            //TODO: Handle circle drawing
            attron(COLOR_PAIR(static_cast<short>(colorPair)));
            for (int i = 0; i < obj.getHeight(); ++i) {
                mvhline(obj.getY() + i, obj.getX(), ' ', obj.getWidth());
            }
            attroff(COLOR_PAIR(static_cast<short>(colorPair)));
        }
    }
    refresh();
}
