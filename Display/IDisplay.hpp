/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** IDisplay
*/

#ifndef IDisplay_HPP_
#define IDisplay_HPP_

class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual int getEvent() = 0;
        virtual void display() = 0;

        virtual void DisplayBackground() = 0;
        

};

extern "C" IDisplay* create();

#endif /* !IDisplay_HPP_ */
