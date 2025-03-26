#ifndef MENU_HPP_
#define MENU_HPP_

#include "../IGame.hpp"
#include <vector>
#include <string>

class Menu : public IGame {
public:
    Menu();
    ~Menu() override = default;

    void reset() override;
    void update(Event event) override;
    std::vector<DisplayObject> getDisplayData() const override;
    int getScore() const override;

private:
    int selectedIndex;
    std::vector<std::string> options;
};

extern "C" IGame* createGame();

#endif
