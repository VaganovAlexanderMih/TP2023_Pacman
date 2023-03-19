#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace MainMenuConstants {
    double font_size = 50;
    double font_name_size = 80;
    std::vector<std::string> options = {"Pacman!", "Play", "Options", "About", "Quit"};
    std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}, {600, 700}, {1100, 700}, {1500, 700}};
    std::vector<double> options_sizes = {80, 50, 50, 50, 50};
    size_t position_first = 1;
}

namespace ChoosingGameModeWindow {
    double font_size = 50;
    double font_name_size = 80;
    std::vector<std::string> options = {"Pacman!", "SinglePlayer", "MultiPlayer"};
    std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}, {1200, 700}};
    std::vector<double> options_sizes = {80, 50, 50};
    size_t position_first = 1;
}

namespace OptionsWindow {
    double font_size = 50;
    double font_name_size = 80;
    std::vector<std::string> options = {"Pacman!", "HardMode", "Enabled? (Red if 'Yes')"};
    std::vector<sf::Vector2f> options_coords = {{680, 40}, {200, 700}, {850, 700}};
    std::vector<double> options_sizes = {80, 50, 50};
    size_t position_first = 1;
}

namespace AboutWindow {
    double font_size = 50;
    double font_name_size = 80;
    std::vector<std::string> options = {"Pacman!", "THIS GAME WAS MADE BY", "ALEXANDER VAGANOV, PAVEL SIDLETSKIY ", "FOR TP COURSE IN MIPT"};
    std::vector<sf::Vector2f> options_coords = {{680, 40}, {550, 200}, {100, 400}, {100, 600}};
    std::vector<double> options_sizes = {80, 50, 50, 50, 50};
    size_t position_first = 1;
}

namespace GameSettings {
    bool hardmode_enabled = false;
    double font_size = 50;
    double font_name_size = 80;
    std::vector<std::string> options = {"Pacman!"};
    std::vector<sf::Vector2f> options_coords = {{680, 40}};
    std::vector<double> options_sizes = {80};
    size_t position_first = 1;
}