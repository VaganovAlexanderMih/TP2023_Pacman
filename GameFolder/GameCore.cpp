/////////////////////////////////////////////////////////
// GAME LOGIC FOR PACMAN                               //
// MADE BY PAVEL SIDLETSKIY                            //
// USED TO GENERATE NEW FRAMES AND CHECK CURRENT STATE //
/////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <set>
#include <unordered_set>

template <typename T>
void D(T n) { std::cout << "DEB " << n << std::endl; }

enum class PlayerState {
  usual, cherry
};
enum class GameMode {
  Normal, Hard
};
enum class GameState {
  Running, Paused, Win, Lose, Caught
};
enum class Colours {
  Red, Blue, White, Yellow
};
enum class Direction {
  None, Up, Right, Down, Left
};
enum class TileState {
  wall, empty, dot, cherry, ulta
};

namespace GameCoreConstants {
  const size_t tile_size = 33;  // need central pixel? Yes
  const size_t def_speed = 2;
  const size_t collision = 200;
};

struct Tile {
  TileState state;
};

struct Map {
  size_t isize = 0;
  size_t jsize = 0;
  std::vector<std::vector<Tile>> tiles;
  std::vector<std::vector<bool>> matrix;

  size_t P(size_t i, size_t j) { return i * jsize + j; }
  size_t C(size_t a, size_t n) {
    if (n == 0) { return a - jsize; }
    if (n == 1) { return a + 1; }
    if (n == 2) { return a + jsize; }
    if (n == 3) { return a - 1; }
    return 0;
  }

  struct FollowState {
    size_t pos;
    Direction InitialState = Direction::None;
    bool operator==(const FollowState& b) const {
      return (pos == b.pos) && (InitialState == b.InitialState);
    }
    bool operator<(const FollowState& b) const {
      return pos < b.pos;
    }
  };

  Direction FollowIntention(size_t a, size_t b) {
    if (a == b) { return Direction::Up; }
    std::set<size_t> touched = {a};
    std::set<FollowState> hist, act;
    if (matrix[a][0]) { hist.insert({a - jsize, Direction::Up}); touched.insert(a - jsize); }
    if (matrix[a][1]) { hist.insert({a + 1, Direction::Right}); touched.insert(a + 1); }
    if (matrix[a][2]) { hist.insert({a + jsize, Direction::Down}); touched.insert(a + jsize); }
    if (matrix[a][3]) { hist.insert({a - 1, Direction::Left}); touched.insert(a - 1); }
    for (auto& i : hist) { if (i.pos == b) return i.InitialState; }
    while (true) {
      for (auto& i : hist) {
        for (size_t j = 0; j < 4; ++j) {
          size_t n = C(i.pos, j);
          if (n == b) { return i.InitialState; }
          if (matrix[i.pos][j] && (touched.count(n) == 0)) {
            touched.insert(n);
            act.insert({n, i.InitialState});
          }
        }
      }
      hist.swap(act);
      act.clear();
    }
  }

  void GenMatrix() {
    matrix = std::vector<std::vector<bool>>(isize * jsize, std::vector<bool>(4, false));
    for (size_t i = 0; i < isize; ++i) {
      for (size_t j = 0; j < jsize; ++j) {
        if (tiles[i][j].state == TileState::wall) { continue; }
        size_t c = P(i, j);
        if (i > 0) { matrix[c][0] = tiles[i - 1][j].state != TileState::wall; }
        if (j < jsize - 1) { matrix[c][1] = tiles[i][j + 1].state != TileState::wall; }
        if (i < isize - 1) { matrix[c][2] = tiles[i + 1][j].state != TileState::wall; }
        if (j > 0) { matrix[c][3] = tiles[i][j - 1].state != TileState::wall; }
      }
    }
  }

  Map() {}
  Map(const std::vector<std::vector<Tile>>& init): tiles(init) {
    isize = tiles.size();
    jsize = tiles[0].size();
    GenMatrix();
  }
    
  Map& operator=(const std::vector<std::vector<Tile>>& init) {
    tiles = init;
    isize = tiles.size();
    jsize = tiles[0].size();
    GenMatrix();
    return *this;
  }
};

struct Coord {
  size_t coordinate = 0;

  size_t GetTile() const;
  static Coord GetCoord(size_t tile);
  std::pair<size_t, size_t> GetDisplayCoord();

  void diff_i(long long diff);
  void diff_j(long long diff);

  size_t GetI() const;
  size_t GetJ() const;

  void SetI(long long i) { diff_i(i - GetI()); }
  void SetJ(long long j) { diff_j(j - GetJ()); }
};
class Creature {
 public:
  Coord coord;
  Direction dir = Direction::None;
  size_t speed = GameCoreConstants::def_speed;

  void GenNextStep(const Direction& new_dir);
};
class Ghost: public Creature {
 public:
  using Creature::coord;
  size_t ticks_to_follow = 0;
  Colours colour = Colours::Red;

  void ThinkAboutLife(size_t i);
};
class Player: public Creature {
 public:
  size_t coins = 0;
  size_t score = 0;
  size_t lifes = 3; // не обязательно
  PlayerState state = PlayerState::usual;
  size_t ticks_for_state = 0;

  void CheckCollisions();
};
namespace GameInfo {
  Map map;
  std::vector<Player> players;
  std::vector<Ghost> ghosts;
  std::vector<Coord> def_players;
  std::vector<Coord> def_ghosts;
  std::vector<Direction> players_int;
  std::vector<Direction> ghosts_int;
  GameMode mode;
  GameState state;
};

struct GameInitInfo {
  std::vector<std::vector<Tile>> init_map;
  std::vector<size_t> init_players;
  std::vector<size_t> init_ghosts;
};

size_t Coord::GetTile() const {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  return ((coordinate / (map.jsize * tile_size)) / (tile_size)) * map.jsize +
         (coordinate % (map.jsize * tile_size)) / tile_size;
}
Coord Coord::GetCoord(size_t tile) {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  size_t i = tile / map.jsize;
  size_t j = tile % map.jsize;
  Coord base;
  base.diff_i(tile_size / 2 + i * tile_size);
  base.diff_j(tile_size / 2 + j * tile_size);
  return base;
}
std::pair<size_t, size_t> Coord::GetDisplayCoord() {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  // returns (x, y), not (i, j)
  return {coordinate % (map.jsize * tile_size), coordinate / (map.jsize * tile_size)};
}
void Coord::diff_i(long long diff) { coordinate += diff * GameInfo::map.jsize * GameCoreConstants::tile_size; }
void Coord::diff_j(long long diff) { coordinate += diff; }
size_t Coord::GetI() const { return coordinate / (GameInfo::map.jsize * GameCoreConstants::tile_size); }
size_t Coord::GetJ() const { return coordinate % (GameInfo::map.jsize * GameCoreConstants::tile_size); }

void Creature::GenNextStep(const Direction& new_dir) {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  switch (new_dir) {
    case (Direction::Up):
      if (map.matrix[coord.GetTile()][0]) dir = new_dir;
      break;
    case (Direction::Right):
      if (map.matrix[coord.GetTile()][1]) dir = new_dir;
      break;
    case (Direction::Down):
      if (map.matrix[coord.GetTile()][2]) dir = new_dir;
      break;
    case (Direction::Left):
      if (map.matrix[coord.GetTile()][3]) dir = new_dir;
      break;
    case (Direction::None):
      break;
  }
  size_t tile = coord.GetTile();
  Coord other_coord = Coord::GetCoord(tile);
  size_t i = other_coord.GetI();
  size_t j = other_coord.GetJ();
  size_t i_cur = coord.GetI();
  size_t j_cur = coord.GetJ();
  long long to_go = def_speed;
  if (i != i_cur && (dir == Direction::Right || dir == Direction::Left)) {
    size_t dist = i + i_cur - std::min(i, i_cur) * 2;
    if (to_go < dist) {
      if (i_cur < i) { coord.diff_i(to_go); return; }
      coord.diff_i(-to_go); return;
    }
    coord.SetI(i);
    to_go -= dist;
  }
  if (j != j_cur && (dir == Direction::Up || dir == Direction::Down)) {
    size_t dist = j + j_cur - std::min(j, j_cur) * 2;
    if (to_go < dist) {
      if (j_cur < j) { coord.diff_j(to_go); return; }
      coord.diff_j(-to_go); return;
    }
    coord.SetJ(j);
    to_go -= dist;
  }
   switch (dir) {
    case (Direction::Up):
      if (i_cur > i || map.matrix[tile][0]) { coord.diff_i(-to_go); }
      break;
    case (Direction::Right):
      if (j_cur < j || map.matrix[tile][1]) { coord.diff_j(to_go); }
      break;
    case (Direction::Down):
      if (i_cur < i || map.matrix[tile][2]) { coord.diff_i(to_go); }
      break;
    case (Direction::Left):
      if (j_cur > j || map.matrix[tile][3]) { coord.diff_j(-to_go); }
      break;
    case (Direction::None):
      break;
  }
}

void Ghost::ThinkAboutLife(size_t i) {
  using namespace GameInfo;
  if (mode == GameMode::Hard) {
    ghosts_int[i] = map.FollowIntention(coord.GetTile(), players[0].coord.GetTile());
  }
}

void Player::CheckCollisions() {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  long long cur_i = coord.GetI();
  long long cur_j = coord.GetJ();
  for (size_t i = 0; i < ghosts.size(); ++i) {
    long long a = ghosts[i].coord.GetI();
    long long b = ghosts[i].coord.GetJ();
    if ((a - cur_i) * (a - cur_i) + (b - cur_j) * (b - cur_j) <= collision) {
      GameInfo::state = GameState::Caught;
      return;
    }
  }
}

// not needed?
size_t FindFreePosition() {
  return 0;
  using namespace GameInfo;
  while (true) {
    size_t ans = rand();
    for (auto& i : players) {
      continue;
    }
  }
}

void ResetPos() {
  using namespace GameInfo;
  for (size_t i = 0; i < ghosts.size(); ++i) {
    ghosts[i].coord = def_ghosts[i];
    ghosts[i].dir = Direction::Up;
    ghosts[i].ticks_to_follow = 0;
  }
  for (size_t i = 0; i < players.size(); ++i) {
    players[i].coord = def_players[i];
    players_int[i] = players[i].dir = Direction::None;
    players[i].state = PlayerState::usual;
    players[i].ticks_for_state = 0;
  }
}

void InitGame(const GameInitInfo& init) {
  using namespace GameInfo;
  using std::vector;
  map = (init.init_map);
  def_players.resize(init.init_players.size());
  for (size_t i = 0; i < def_players.size(); ++i) {
    def_players[i] = Coord::GetCoord(init.init_players[i]);
  }
  def_ghosts.resize(init.init_ghosts.size());
  for (size_t i = 0; i < def_ghosts.size(); ++i) {
    def_ghosts[i] = Coord::GetCoord(init.init_ghosts[i]);
  }
  players = std::vector<Player>(init.init_players.size());
  ghosts = std::vector<Ghost>(init.init_ghosts.size());
  players_int = std::vector<Direction>(players.size(), Direction::None);
  ghosts_int = std::vector<Direction>(ghosts.size(), Direction::Up);
  state = GameState::Running;
  mode = GameMode::Hard;
  ResetPos();
}

void GenNextFrame() {
  using namespace GameInfo;
  using namespace GameCoreConstants;
  for (size_t i = 0; i < players.size(); ++i) {
    players[i].GenNextStep(players_int[i]);
  }
  for (size_t i = 0; i < ghosts.size(); ++i) {
    ghosts[i].ThinkAboutLife(i);
    ghosts[i].GenNextStep(ghosts_int[i]);
  }
  for (size_t i = 0; i < players.size(); ++i) {
    players[i].CheckCollisions();
    if (state == GameState::Caught) {
      ResetPos();
      state = GameState::Running;
    }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
