/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** SDL2
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../IDisplay.hpp"
#include "../include/DisplayObject.hpp"
#include "../include/Event.hpp"


#ifndef SDL2_HPP_
#define SDL2_HPP_

class SDL2 : public IDisplay {
    public:
        SDL2();
        ~SDL2();

        void init(int width, int height) override;
        void stop() override;

        Event pollEvent() override;

        void clear() override;
        void display(const std::vector<DisplayObject>& objects) override;
    private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    TTF_Font* _font;
    SDL_Color _textColor;
};

extern "C" IDisplay* create()
{
    return new SDL2();
}

#endif /* !SDL2_HPP_ */
