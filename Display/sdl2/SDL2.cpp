/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2.cpp
*/

#include "SDL2.hpp"

SDL2::SDL2() {
}

SDL2::~SDL2() {
    SDL_Quit();
}


void SDL2::init(int width, int height) 
{
    _window = SDL_CreateWindow(
        "Window SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    DL_ShowCursor(SDL_DISABLE);
    //_font = TTF_OpenFont("Font.ttf", 3); //en vérité je ne sais pas quelle font size il faut mettre donc c'est assez aléatoire
    //SDL_Color _textColor = {255, 255, 255};
    _running = true;
}

void SDL2::stop() 
{
    _running = false;
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

Event SDL2::pollEvent() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keycode = event.key.keysym.sym;
            switch (keycode) {
                case SDLK_UP:
                    return {
                        EventType::KEY_PRESSED,
                        Key::UP,
                        {-1, -1, -1}
                    };
                case SDLK_DOWN:
                    return {
                        EventType::KEY_PRESSED,
                        Key::DOWN,
                        {-1, -1, -1}
                    };
                case SDLK_LEFT:
                    return {
                        EventType::KEY_PRESSED,
                        Key::LEFT,
                        {-1, -1, -1}
                    };
                case SDLK_RIGHT:
                    return {
                        EventType::KEY_PRESSED,
                        Key::RIGHT,
                        {-1, -1, -1}
                    };                
                case SDLK_SPACE:
                    return {
                        EventType::KEY_PRESSED,
                        Key::SPACE,
                        {-1, -1, -1}
                    };
                case SDLK_RETURN:
                    return {
                        EventType::KEY_PRESSED,
                        Key::ENTER,
                        {-1, -1, -1}
                    };
                case SDLK_ESCAPE:
                    return {
                        EventType::KEY_PRESSED,
                        Key::ESCAPE,
                        {-1, -1, -1}
                    };
                case SDLK_BACKSPACE:
                    return {
                        EventType::KEY_PRESSED,
                        Key::BACKSPACE,
                        {-1, -1, -1}
                    };
                case SDLK_F1:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F1,
                        {-1, -1, -1}
                    };
                case SDLK_F2:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F2,
                        {-1, -1, -1}
                    };
                case SDLK_F3:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F3,
                        {-1, -1, -1}
                    };
                case SDLK_F4:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F4,
                        {-1, -1, -1}
                    };
                case SDLK_F5:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F5,
                        {-1, -1, -1}
                    };
                case SDLK_F6:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F6,
                        {-1, -1, -1}
                    };
                case SDLK_F7:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F7,
                        {-1, -1, -1}
                    };
                case SDLK_F8:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F8,
                        {-1, -1, -1}
                    };
                case SDLK_F9:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F9,
                        {-1, -1, -1}
                    };
                case SDLK_F10:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F10,
                        {-1, -1, -1}
                    };
                case SDLK_F11:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F11,
                        {-1, -1, -1}
                    };
                case SDLK_F12:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F12,
                        {-1, -1, -1}
                    };
                case SDLK_a:
                case SDLK_A:
                    return {
                        EventType::KEY_PRESSED,
                        Key::A,
                        {-1, -1, -1}
                    };
                case SDLK_b:
                case SDLK_B:
                    return {
                        EventType::KEY_PRESSED,
                        Key::B,
                        {-1, -1, -1}
                    };
                case SDLK_c:
                case SDLK_C:
                    return {
                        EventType::KEY_PRESSED,
                        Key::C,
                        {-1, -1, -1}
                    };
                case SDLK_d:
                case SDLK_D:
                    return {
                        EventType::KEY_PRESSED,
                        Key::D,
                        {-1, -1, -1}
                    };
                case SDLK_e:
                case SDLK_E:
                    return {
                        EventType::KEY_PRESSED,
                        Key::E,
                        {-1, -1, -1}
                    };
                case SDLK_f:
                case SDLK_F:
                    return {
                        EventType::KEY_PRESSED,
                        Key::F,
                        {-1, -1, -1}
                    };
                case SDLK_g:
                case SDLK_G:
                    return {
                        EventType::KEY_PRESSED,
                        Key::G,
                        {-1, -1, -1}
                    };
                case SDLK_h:
                case SDLK_H:
                    return {
                        EventType::KEY_PRESSED,
                        Key::H,
                        {-1, -1, -1}
                    };
                case SDLK_i:
                case SDLK_I:
                    return {
                        EventType::KEY_PRESSED,
                        Key::I,
                        {-1, -1, -1}
                    };
                case SDLK_j:
                case SDLK_J:
                    return {
                        EventType::KEY_PRESSED,
                        Key::J,
                        {-1, -1, -1}
                    };
                case SDLK_k:
                case SDLK_K:
                    return {
                        EventType::KEY_PRESSED,
                        Key::K,
                        {-1, -1, -1}
                    };
                case SDLK_l:
                case SDLK_L:
                    return {
                        EventType::KEY_PRESSED,
                        Key::L,
                        {-1, -1, -1}
                    };
                case SDLK_m:
                case SDLK_M:
                    return {
                        EventType::KEY_PRESSED,
                        Key::M,
                        {-1, -1, -1}
                    };
                case SDLK_n:
                case SDLK_N:
                    return {
                        EventType::KEY_PRESSED,
                        Key::N,
                        {-1, -1, -1}
                    };
                case SDLK_o:
                case SDLK_O:
                    return {
                        EventType::KEY_PRESSED,
                        Key::O,
                        {-1, -1, -1}
                    };
                case SDLK_p:
                case SDLK_P:
                    return {
                        EventType::KEY_PRESSED,
                        Key::P,
                        {-1, -1, -1}
                    };
                case SDLK_q:
                case SDLK_Q:
                    return {
                        EventType::KEY_PRESSED,
                        Key::Q,
                        {-1, -1, -1}
                    };
                case SDLK_r:
                case SDLK_R:
                    return {
                        EventType::KEY_PRESSED,
                        Key::R,
                        {-1, -1, -1}
                    };
                case SDLK_s:
                case SDLK_S:
                    return {
                        EventType::KEY_PRESSED,
                        Key::S,
                        {-1, -1, -1}
                    };
                case SDLK_t:
                case SDLK_T:
                    return {
                        EventType::KEY_PRESSED,
                        Key::T,
                        {-1, -1, -1}
                    };
                case SDLK_u:
                case SDLK_U:
                    return {
                        EventType::KEY_PRESSED,
                        Key::U,
                        {-1, -1, -1}
                    };
                case SDLK_v:
                case SDLK_V:
                    return {
                        EventType::KEY_PRESSED,
                        Key::V,
                        {-1, -1, -1}
                    };
                case SDLK_w:
                case SDLK_W:
                    return {
                        EventType::KEY_PRESSED,
                        Key::W,
                        {-1, -1, -1}
                    };
                case SDLK_x:
                case SDLK_X:
                    return {
                        EventType::KEY_PRESSED,
                        Key::X,
                        {-1, -1, -1}
                    };
                case SDLK_y:
                case SDLK_Y:
                    return {
                        EventType::KEY_PRESSED,
                        Key::Y,
                        {-1, -1, -1}
                    };
                case SDLK_z:
                case SDLK_Z:
                    return {
                        EventType::KEY_PRESSED,
                        Key::Z,
                        {-1, -1, -1}
                    };
                default: return Key::NONE;
            }
        }
    }

    return Key::NONE;
}

void SDL2::clear() 
{
    SDL_RenderClear(_renderer);
}

void SDL2::display(const std::vector<DisplayObject>& objects) 
{
    for (const auto& obj : objects) {
        SDL_SetRenderDrawColor(_renderer, obj.getColor().r, obj.getColor().g, obj.getColor().b, obj.getColor().a);

        switch (obj.getType()) {
            case ObjectType::RECTANGLE:
                SDL_Rect rect = { obj.getX(), obj.getY(), obj.getWidth(), obj.getHeight() };
                SDL_RenderFillRect(_renderer, &rect);
                break;
            case ObjectType::TEXT:
                std::cout << "Affichage du texte: " << obj.getText() << std::endl;
                break;

            case ObjectType::SPRITE:
                break;

            case ObjectType::CUSTOM:
                break;

            case ObjectType::CIRCLE:
                for (int i = 0; i < obj.getHeight(); ++i) {
                    int offsetX = obj.getWidth() / 2;
                    int offsetY = obj.getHeight() / 2;
                    for (int j = 0; j < obj.getWidth(); ++j) {
                        int dx = j - offsetX;
                        int dy = i - offsetY;
                        if (dx * dx + dy * dy <= offsetX * offsetX) {
                            SDL_RenderDrawPoint(_renderer, obj.getX() + j, obj.getY() + i);
                        }
                    }
                }
                break;
        }
    }
    SDL_RenderPresent(_renderer);
}
