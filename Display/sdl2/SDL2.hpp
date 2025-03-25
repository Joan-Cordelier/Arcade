/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** SDL2
*/

#include "../IDisplay.hpp"

#ifndef SDL2_HPP_
#define SDL2_HPP_

class SDL2 : public IDisplay {
    public:
        SDL2();
        ~SDL2();

        int getEvent() override;
        void display() override;

    protected:
    private:
};

extern "C" IDisplay* create() {
    return new SDL2();
}

#endif /* !SDL2_HPP_ */
