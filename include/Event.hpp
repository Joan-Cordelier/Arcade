/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** Event.hpp
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

enum class EventType {
    NONE,
    KEY_PRESSED,
    KEY_RELEASED,
    MOUSE_PRESSED,
    MOUSE_RELEASED,
    MOUSE_MOVED,
    EXIT
};

enum class Key {
    NONE,
    UP, DOWN, LEFT, RIGHT,
    SPACE,
    ENTER,
    ESCAPE,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
    LSHIFT, RSHIFT,
    LCTRL, RCTRL,
    LALT, RALT,
    CAPSLOCK,
    TAB, BACKSPACE,
};

struct MouseEvent {
    int x;
    int y;
    int button;
};

struct Event {
    EventType type;
    Key key;
    MouseEvent mouse;
};

#endif /* !EVENT_HPP_ */