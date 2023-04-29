#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace CommonConstants {
    const double font_size = 50;
    const double font_name_size = 80;
    const size_t position_first = 1;
}

namespace MainMenuConstants {
    const std::vector<std::string> options = {"Pacman!", "Play", "Options", "About", "Quit"};
    const std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}, {600, 700}, {1100, 700}, {1500, 700}};
    const std::vector<double> options_sizes = {80, 50, 50, 50, 50};
}

namespace ChoosingGameModeWindow {
    const std::vector<std::string> options = {"Pacman!", "SinglePlayer"};
    const std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}};
    const std::vector<double> options_sizes = {80, 50};
}

namespace OptionsWindow {
    const std::vector<std::string> options = {"Pacman!", "HardMode", "Enabled? (Red if 'Yes')"};
    const std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}, {850, 700}};
    const std::vector<double> options_sizes = {80, 50, 50};
}

namespace AboutWindow {
    const std::vector<std::string> options = {"Pacman!", "THIS GAME WAS MADE BY", "ALEXANDER VAGANOV, PAVEL SIDLETSKIY ", "FOR TP COURSE IN MIPT"};
    const std::vector<sf::Vector2f> options_coords = {{680, 40}, {550, 200}, {100, 400}, {100, 600}};
    const std::vector<double> options_sizes = {80, 50, 50, 50, 50};
}

namespace GameSettings {
    inline bool hardmode_enabled = false;
    const std::vector<std::string> options = {"Pacman!"};
    const std::vector<sf::Vector2f> options_coords = {{680, 40}};
    const std::vector<double> options_sizes = {80};
}