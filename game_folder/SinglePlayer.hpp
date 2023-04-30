#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameMenu.hpp"
#include "Maps.hpp"

inline bool flag_continuing = false;

std::string IntToStr(size_t number);

void CheckTouches();

void Game();