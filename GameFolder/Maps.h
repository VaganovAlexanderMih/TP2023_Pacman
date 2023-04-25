#pragma once
#include <vector>
#include "GameCore.h"
#include <sstream>
#include <fstream>
#include <iterator>

int StrToInt(std::string& str) {
  int number = 0;
  int start;
  for (int i = start; str[i]; i++) {
    number = (number * 10) + (str[i] - '0');
  }
  return number;
}

std::vector<std::vector<int>> GettingMap() {
  std::vector<std::vector<Tile>> map;
  std::vector<size_t> players;
  std::vector<size_t> ghosts;
  std::fstream file_in("Maps.txt");
  std::string line;
  int count = 0;
  while (std::getline(file_in, line)) {
    std::istringstream ss(line);
    if (line == "") {
      ++count;
    }
    if (count == 0) {
      map.emplace_back(std::istream_iterator<int>(ss), std::istream_iterator<int>());
    } else if (count == 1) {
      players.push_back(StrToInt(line));
    } else {
      ghosts.emplace_back(std::istream_iterator<int>(ss), std::istream_iterator<int>());
    }
  }
}