#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameMenu.h"
#include "GameCore.h"
#include "Maps.h"

bool flag = false;

void CheckTouches() {
  using namespace GameInfo;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    players_int[0] = Direction::Left;
    //D("Left");
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    players_int[0] = Direction::Up;
    //D("Up");
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    players_int[0] = Direction::Right;
    //D("Right");
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    players_int[0] = Direction::Down;
    //D("Down");
  }
}

void Game() {
  GameMenu* game_menu = new GameMenu(GameSettings::options, "../sprites/wall.png", GameSettings::options_coords, GameSettings::options_sizes, 1, 5);
  using namespace GameInfo;

  if (!flag) {
    D("Initialising game");
    InitGame(map1);
    flag = true;
  }
  // GameState status = GameState::Running; инициализация должна быть
  std::cout << "Entering Game" << std::endl;
  using namespace WindowSettings;
  using namespace GameInfo;
  using namespace GameCoreConstants;
  GameState status = GameState::Running;
  D(static_cast<int>(status));
  while (game_menu->window_id == 5 || game_menu->window_id == 6) {
    sf::Event event;
    game_menu->window->clear();
    sf::RectangleShape next_menu;
    sf::Sprite player;
    sf::Texture texture;
    if (status == GameState::Running) {
      GenNextFrame();
      game_menu->window->clear();
      double offset_x = static_cast<double>((wigth - tile_wight * map.jsize) / 2);
      double offset_y = static_cast<double>((height - tile_height * map.isize) / 2);
      for (size_t i = 0; i < map.isize; ++i) {
        for (size_t j = 0; j < map.jsize; ++j) {
          sf::Sprite square;
          // D(square.getSize().x);
          // D(square.getSize().y);
          square.setPosition(offset_x + tile_wight * j,
                             offset_y + tile_height * i);
          if (map.tiles[i][j].state == TileState::wall) {
            texture.loadFromFile("../sprites/wall.png");
            square.setTexture(texture);
            //std::cout << "Texture was loaded" << std::endl;
          } else if (map.tiles[i][j].state == TileState::empty) {
            texture.loadFromFile("../sprites/empty.png");
            square.setTexture(texture);
          } else if (map.tiles[i][j].state == TileState::dot) {
            texture.loadFromFile("../sprites/dot.png");
            square.setTexture(texture);
          } else if (map.tiles[i][j].state == TileState::cherry) {
            texture.loadFromFile("../sprites/cherry.png");
            square.setTexture(texture);
          } else if (map.tiles[i][j].state == TileState::ulta) {
            texture.loadFromFile("../sprites/ulta.png");
            square.setTexture(texture);
          }
          game_menu->window->draw(square);
        }
      }
      std::pair<size_t, size_t> player_display_coords =
          GameInfo::players[0].coord.GetDisplayCoord();
      player.setPosition(offset_x - 15 + player_display_coords.first,
                         offset_y - 15 + player_display_coords.second);
      if (players[0].dir == Direction::None || players[0].dir == Direction::Right) {
        texture.loadFromFile("../sprites/player_right.png");
      } else if (players[0].dir == Direction::Up) {
        texture.loadFromFile("../sprites/player_up.png");
      } else if (players[0].dir == Direction::Down) {
        texture.loadFromFile("../sprites/player_down.png");
      } else if (players[0].dir == Direction::Left) {
        texture.loadFromFile("../sprites/player_left.png");
      }
      player.setTexture(texture);
      game_menu->window->draw(player);
      for (size_t i = 0; i < GameInfo::ghosts.size(); ++i) {
        std::pair<size_t, size_t> ghost_display_coords =
            GameInfo::ghosts[i].coord.GetDisplayCoord();
        sf::Sprite ghost;
        sf::Texture texture;
        ghost.setPosition(offset_x - 15 + ghost_display_coords.first,
                          offset_y - 15 + ghost_display_coords.second);
        if (ghosts[i].dir == Direction::None || ghosts[i].dir == Direction::Right) {
          texture.loadFromFile("../sprites/ghost_right.png");
        } else if (ghosts[i].dir == Direction::Up) {
          texture.loadFromFile("../sprites/ghost_up.png");
        } else if (ghosts[i].dir == Direction::Down) {
          texture.loadFromFile("../sprites/ghost_down.png");
        } else if (ghosts[i].dir == Direction::Left) {
          texture.loadFromFile("../sprites/ghost_left.png");
        }
        ghost.setTexture(texture);
        game_menu->window->draw(ghost);
      }
      CheckTouches();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        status = GameState::Paused;
        break;
      }
      game_menu->window->display();
    } else if (status == GameState::Paused) {
      sf::Event event;
      next_menu.setSize(sf::Vector2f(1920, 1080));
      texture.loadFromFile("../sprites/paused.png");
      //next_menu.setTexture(texture);
      while (status == GameState::Paused) {
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game_menu->next_menu_id = 1;
            flag = false;
            D(flag);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            status = GameState::Running;
            break;
          }
        }
      }
    } else if (status == GameState::Win) {
      next_menu.setSize(sf::Vector2f(1920, 1080));
      texture.loadFromFile("../sprites/win.png");
      //next_menu.setTexture(texture);
      while (status == GameState::Win) {
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game_menu->next_menu_id = 1;
            flag = false;
            break;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            status = GameState::Running;
          }
        }
      }
    } else if (status == GameState::Lose) {
      next_menu.setSize(sf::Vector2f(1920, 1080));
      texture.loadFromFile("../sprites/lose.png");
      //next_menu.setTexture(texture);
      while (status == GameState::Win) {
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game_menu->next_menu_id = 1;
            flag = false;
            break;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            status = GameState::Running;
          }
        }
      }
    } else if (status == GameState::Caught) {
      // Caught animation
    }
    if (event.type == sf::Event::KeyPressed) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        status = GameState::Paused;
      }
    }
  }
}