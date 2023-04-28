#include <vector>
#include "GameCore.cpp"
#include <sstream>
#include <fstream>
#include <iterator>

int StrToInt(std::string& str) {
  int number = 0;
  for (int i = 0; str[i]; i++) {
    number = (number * 10) + (str[i] - '0');
  }
  return number;
}

GameInitInfo GettingMap() {
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
    } else {
      if (count == 0) {
        map.emplace_back(std::istream_iterator<int>(ss), std::istream_iterator<int>());
      } else if (count == 1) {
        std::cout << "Map was builded" << std::endl;
        players.push_back(StrToInt(line));
      } else {
        std::cout << "Players were set" << std::endl;
        std::string number = "";
        for (auto num : line) {
          if (num == ' ') {
            ghosts.push_back(StrToInt(number));
            number = "";
          } else {
            number += num;
          }
        }
        ghosts.push_back(StrToInt(number));
      }
    }
  }
  return {map, players, ghosts};
}

GameInitInfo map1 = GettingMap();