/*
** EPITECH PROJECT, 2025
** B-OOP-400-TLS-4-1-arcade-melissa.muller
** File description:
** main
*/

#include <iostream>
#include "Arcade.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2) {
            throw std::invalid_argument("Usage: ./arcade <graphical_library_path.so>");
        }
        Arcade arcade(av[2]);
        return 0;
    }
    catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return 84;
    }
}
