#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameMenu.hpp"
#include "Maps.hpp"

inline bool flag_continuing = false;

inline bool end_of_the_game = false;

void CheckTouches();

void Game();