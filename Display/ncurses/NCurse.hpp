/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** NCurse
*/

#include "../IDisplay.hpp"

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

class NCurse : public IDisplay {
    public:
        NCurse();
        ~NCurse();

        int getEvent() override;
        void display() override;

    protected:
    private:
};

extern "C" IDisplay* create() {
    return new NCurse();
}

#endif /* !NCURSE_HPP_ */
