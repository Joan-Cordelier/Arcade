/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2.cpp
*/

#include "SDL2.hpp"

SDL2::SDL2() {
    _window = nullptr;
    _renderer = nullptr;
    _font = nullptr;
    _running = false;
}

SDL2::~SDL2() {
    stop();
}

void SDL2::init(int width, int height) 
{
    if (_running) {
        stop();
    }
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    
    _window = SDL_CreateWindow(
        "Window SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width * 2.25,
        height * 1.75,
        SDL_WINDOW_SHOWN
    );
    
    if (!_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return;
    }
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        _window = nullptr;
        TTF_Quit();
        SDL_Quit();
        return;
    }
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    
    _font = TTF_OpenFont("Display/assets/font.ttf", 20);
    if (!_font) {
        std::cerr << "Font could not be loaded! TTF_Error: " << TTF_GetError() << std::endl;
    }
    
    _running = true;
}

void SDL2::stop() 
{
    if (!_running)
        return;
        
    _running = false;
    
    if (_font != nullptr) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    
    if (_renderer != nullptr) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    
    if (_window != nullptr) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    
    TTF_Quit();
    SDL_Quit();
}

Event SDL2::pollEvent() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keycode = event.key.keysym.sym;
            switch (keycode) {
            case SDLK_UP: return { EventType::KEY_PRESSED, Key::UP, {-1, -1, -1} };
            case SDLK_DOWN: return { EventType::KEY_PRESSED, Key::DOWN, {-1, -1, -1} };
            case SDLK_LEFT: return { EventType::KEY_PRESSED, Key::LEFT, {-1, -1, -1} };
            case SDLK_RIGHT: return { EventType::KEY_PRESSED, Key::RIGHT, {-1, -1, -1} };
            case SDLK_SPACE: return { EventType::KEY_PRESSED, Key::SPACE, {-1, -1, -1} };
            case SDLK_RETURN: return { EventType::KEY_PRESSED, Key::ENTER, {-1, -1, -1} };
            case SDLK_ESCAPE: return { EventType::KEY_PRESSED, Key::ESCAPE, {-1, -1, -1} };
            case SDLK_BACKSPACE: return { EventType::KEY_PRESSED, Key::BACKSPACE, {-1, -1, -1} };
            case SDLK_F1: return { EventType::KEY_PRESSED, Key::F1, {-1, -1, -1} };
            case SDLK_F2: return { EventType::KEY_PRESSED, Key::F2, {-1, -1, -1} };
            case SDLK_F3: return { EventType::KEY_PRESSED, Key::F3, {-1, -1, -1} };
            case SDLK_F4: return { EventType::KEY_PRESSED, Key::F4, {-1, -1, -1} };
            case SDLK_F5: return { EventType::KEY_PRESSED, Key::F5, {-1, -1, -1} };
            case SDLK_F6: return { EventType::KEY_PRESSED, Key::F6, {-1, -1, -1} };
            case SDLK_F7: return { EventType::KEY_PRESSED, Key::F7, {-1, -1, -1} };
            case SDLK_F8: return { EventType::KEY_PRESSED, Key::F8, {-1, -1, -1} };
            case SDLK_F9: return { EventType::KEY_PRESSED, Key::F9, {-1, -1, -1} };
            case SDLK_F10: return { EventType::KEY_PRESSED, Key::F10, {-1, -1, -1} };
            case SDLK_F11: return { EventType::KEY_PRESSED, Key::F11, {-1, -1, -1} };
            case SDLK_F12: return { EventType::KEY_PRESSED, Key::F12, {-1, -1, -1} };
            case SDLK_a: return { EventType::KEY_PRESSED, Key::A, {-1, -1, -1} };
            case SDLK_b: return { EventType::KEY_PRESSED, Key::B, {-1, -1, -1} };
            case SDLK_c: return { EventType::KEY_PRESSED, Key::C, {-1, -1, -1} };
            case SDLK_d: return { EventType::KEY_PRESSED, Key::D, {-1, -1, -1} };
            case SDLK_e: return { EventType::KEY_PRESSED, Key::E, {-1, -1, -1} };
            case SDLK_f: return { EventType::KEY_PRESSED, Key::F, {-1, -1, -1} };
            case SDLK_g: return { EventType::KEY_PRESSED, Key::G, {-1, -1, -1} };
            case SDLK_h: return { EventType::KEY_PRESSED, Key::H, {-1, -1, -1} };
            case SDLK_i: return { EventType::KEY_PRESSED, Key::I, {-1, -1, -1} };
            case SDLK_j: return { EventType::KEY_PRESSED, Key::J, {-1, -1, -1} };
            case SDLK_k: return { EventType::KEY_PRESSED, Key::K, {-1, -1, -1} };
            case SDLK_l: return { EventType::KEY_PRESSED, Key::L, {-1, -1, -1} };
            case SDLK_m: return { EventType::KEY_PRESSED, Key::M, {-1, -1, -1} };
            case SDLK_n: return { EventType::KEY_PRESSED, Key::N, {-1, -1, -1} };
            case SDLK_o: return { EventType::KEY_PRESSED, Key::O, {-1, -1, -1} };
            case SDLK_p: return { EventType::KEY_PRESSED, Key::P, {-1, -1, -1} };
            case SDLK_q: return { EventType::KEY_PRESSED, Key::Q, {-1, -1, -1} };
            case SDLK_r: return { EventType::KEY_PRESSED, Key::R, {-1, -1, -1} };
            case SDLK_s: return { EventType::KEY_PRESSED, Key::S, {-1, -1, -1} };
            case SDLK_t: return { EventType::KEY_PRESSED, Key::T, {-1, -1, -1} };
            case SDLK_u: return { EventType::KEY_PRESSED, Key::U, {-1, -1, -1} };
            case SDLK_v: return { EventType::KEY_PRESSED, Key::V, {-1, -1, -1} };
            case SDLK_w: return { EventType::KEY_PRESSED, Key::W, {-1, -1, -1} };
            case SDLK_x: return { EventType::KEY_PRESSED, Key::X, {-1, -1, -1} };
            case SDLK_y: return { EventType::KEY_PRESSED, Key::Y, {-1, -1, -1} };
            case SDLK_z: return { EventType::KEY_PRESSED, Key::Z, {-1, -1, -1} };
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int mousex = static_cast<int>(std::floor(event.button.x / 32));
            int mousey = static_cast<int>(std::floor(event.button.y / 32));
            return {
                EventType::MOUSE_PRESSED,
                Key::NONE,
                {mousex, mousey, 1}
            };
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
            int mousex = static_cast<int>(std::floor(event.button.x / 32));
            int mousey = static_cast<int>(std::floor(event.button.y / 32));
            return {
                EventType::MOUSE_PRESSED,
                Key::NONE,
                {mousex, mousey, 2}
            };
        }
    }

    return {
            EventType::NONE,
            Key::NONE,
            {-1, -1, -1}
        };
}

void SDL2::clear() 
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SDL2::display(const std::vector<DisplayObject>& objects) 
{
    for (const auto& obj : objects) {
        SDL_SetRenderDrawColor(_renderer, obj.getColor().r, obj.getColor().g, obj.getColor().b, obj.getColor().a);
        ObjectType type = obj.getType();
            if (type == ObjectType::RECTANGLE) {
                int scaledWidth = static_cast<int>(obj.getWidth() * obj.getScaleX() * 32.0f);
                int scaledHeight = static_cast<int>(obj.getHeight() * obj.getScaleY() * 32.0f);
                SDL_Rect rect = { obj.getX() * 32, obj.getY() * 32, scaledWidth, scaledHeight};
                SDL_RenderFillRect(_renderer, &rect);
            }
            if (type == ObjectType::TEXT) {
                    SDL_Surface* surf = TTF_RenderText_Solid(_font, obj.getText().c_str(), {obj.getColor().r, obj.getColor().g, obj.getColor().b, obj.getColor().a});
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surf);
                    SDL_FreeSurface(surf);
                    SDL_Rect textrect = {obj.getX() * 32, obj.getY() * 32, obj.getWidth() * obj.getScaleX() * 32, obj.getHeight() * obj.getScaleY() * 32};
                    SDL_RenderCopy(_renderer, texture, nullptr, &textrect);
                    SDL_DestroyTexture(texture);
            }
            if (type == ObjectType::SPRITE) {
            }
            if (type  == ObjectType::CUSTOM) {
            }
            if (type == ObjectType::CIRCLE) {
                for (int i = 0; i < obj.getHeight() * 32; ++i) {
                    int offsetX = obj.getWidth() * 32 / 2;
                    int offsetY = obj.getHeight() * 32 / 2;
                    for (int j = 0; j < obj.getWidth() * 32; ++j) {
                        int dx = j - offsetX;
                        int dy = i - offsetY;
                        if (dx * dx + dy * dy <= offsetX * offsetX) {
                            SDL_RenderDrawPoint(_renderer, obj.getX() * 32 + j, obj.getY() * 32 + i);
                        }
                    }
                }
            }
    }
    SDL_RenderPresent(_renderer);
}

extern "C" IDisplay* createDisplay() {
    return new SDL2();
}
