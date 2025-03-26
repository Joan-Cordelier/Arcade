#include "Menu.hpp"

Menu::Menu() {
    options = { "Start Game", "High Scores", "Exit" };
    selectedIndex = 0;
}

void Menu::reset() {
    selectedIndex = 0;
}

void Menu::update(Event event) {
    if (event == Event::UP && selectedIndex > 0)
        selectedIndex--;
    else if (event == Event::DOWN && selectedIndex < options.size() - 1)
        selectedIndex++;
    else if (event == Event::VALIDATE) {
    }
}

std::vector<DisplayObject> Menu::getDisplayData() const {
    std::vector<DisplayObject> data;
    int y = 5;

    for (size_t i = 0; i < options.size(); ++i) {
        std::string text = (i == selectedIndex ? "> " : "  ") + options[i];
        data.push_back(DisplayObject{5, static_cast<int>(y + i), TileType::TEXT, text});
    }

    return data;
}

int Menu::getScore() const {
    return 0;
}

extern "C" IGame* createGame() {
    return new Menu();
}
