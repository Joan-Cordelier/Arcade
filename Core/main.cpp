/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** main.cpp
*/

#include <iostream>
#include <stdexcept>
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [graphical_library_path]" << std::endl;
        return 84;
    }

    try {
        Core core(av[1]);
        core.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
