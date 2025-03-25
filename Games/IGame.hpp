/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void Play() = 0;
        virtual void DoEvent(int event) = 0;

    protected:
    private:
};

extern "C" IGame* createGame();

#endif 
