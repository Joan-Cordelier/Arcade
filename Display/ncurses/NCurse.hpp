/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** NcurseDisplayer
*/

#include <vector>
#include <ncurses.h>
#include <thread>
#include <iostream>
#include "../IDisplay.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"

#ifndef NcurseDisplayer_HPP_
#define NcurseDisplayer_HPP_

class NcurseDisplayer : public IDisplay {
    public:
        NcurseDisplayer();
        ~NcurseDisplayer() override;

        void init(int width, int height) override;
        void stop() override;

        Event pollEvent() override;

        void clear() override;
        void display(const std::vector<DisplayObject>& objects) override;

    private:
        bool _running = false;
        int _colorPairCount = 0;
        std::vector<Color> _colors;
        WINDOW *_window = nullptr;
        int _width = 0;
        int _height = 0;

        int createColorPair(const Color& color);

        int _scaleX;
        int _scaleY;
        int _originalWidth;
        int _originalHeight;
};

extern "C" IDisplay *createDisplay();

#endif /* !NcurseDisplayer_HPP_ */
