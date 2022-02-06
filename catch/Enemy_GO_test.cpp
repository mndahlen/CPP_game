#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/GameObject/DynamicObject/Enemy/Enemy.hpp"
#include "../TowerDefence/DataHandler/DataHandler.hpp"

TEST_CASE("Enemy initialization")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["enemy"]["covid"]["parameters"]["1"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    sf::Vector2f coordinates_e (1,1);
    sf::Vector2f coordinates (2,2);
    std::vector<sf::Vector2f> road_vector;
    road_vector.push_back(coordinates_e);
    road_vector.push_back(coordinates);

  try
  {
      sf::Vector2f coordinates_e (1,1);
      sf::Vector2f coordinates (2,2);
      std::vector<sf::Vector2f> road_vector;
      road_vector.push_back(coordinates_e);
      road_vector.push_back(coordinates);

      Enemy nme(1.0, 1.0, texture, config, &road_vector);
      SUCCEED();
  }
  catch(const std::exception& e)
  {
      std::cerr << e.what() << '\n';

      FAIL();
  }

}

TEST_CASE("getters, setters, return correct values")
{
  DataHandler dh("../TowerDefence/config/config.json");
  nlohmann::json config;
  config = dh.getConfig()["game_entity"]["enemy"]["covid"]["parameters"]["1"];
  sf::Texture test_texture;
  std::vector<sf::Texture *> texture;
  texture.push_back(&test_texture);

  sf::Vector2f coordinates_e (1,1);
  sf::Vector2f coordinates (2,2);
  std::vector<sf::Vector2f> road_vector;
  road_vector.push_back(coordinates_e);
  road_vector.push_back(coordinates);

  Enemy nme(1.0, 1.0, texture, config, &road_vector);

  int speed{config["speed"]};
  int hp{config["hp"]};
  int dmg{config["dmg"]};

  CHECK(nme.getSpeed() == speed);
  CHECK(nme.getHp() == hp);
  CHECK(nme.getDamage() == dmg);
  CHECK(nme.getPosition() == coordinates_e);

  nme.setPosition(2,2);

  CHECK(nme.getPosition() == coordinates);
}

TEST_CASE("updateObject() correct movement")
{
  DataHandler dh("../TowerDefence/config/config.json");
  nlohmann::json config;
  config = dh.getConfig()["game_entity"]["enemy"]["covid"]["parameters"]["1"];
  sf::Texture test_texture;
  std::vector<sf::Texture *> texture;
  texture.push_back(&test_texture);
  int speed{config["speed"]};

  sf::Vector2f coordinates (1,1);
  sf::Vector2f coordinates2 (4,1);
  std::vector<sf::Vector2f> road_vector;
  road_vector.push_back(coordinates);
  road_vector.push_back(coordinates2);

  Enemy nme(1.0, 1.0, texture, config, &road_vector);
  nme.updateObject();
  sf::Vector2f coordinates_(1 + speed, 1);
  CHECK(nme.getPosition() == coordinates_);
}

TEST_CASE("updateObject() correct movement, more then one point")
{
  DataHandler dh("../TowerDefence/config/config.json");
  nlohmann::json config;
  config = dh.getConfig()["game_entity"]["enemy"]["covid"]["parameters"]["1"];
  sf::Texture test_texture;
  std::vector<sf::Texture *> texture;
  texture.push_back(&test_texture);

  int speed{config["speed"]};
  sf::Vector2f coordinates (1,1);
  sf::Vector2f coordinates2 (1 + speed, 1);
  sf::Vector2f coordinates3 (1 + speed, 1 + 3*speed);
  std::vector<sf::Vector2f> road_vector;
  road_vector.push_back(coordinates);
  road_vector.push_back(coordinates2);
  road_vector.push_back(coordinates3);

  Enemy nme(1.0, 1.0, texture, config, &road_vector);
  nme.updateObject();
  nme.updateObject();
  sf::Vector2f coordinates_(1 + speed, 1 + speed);
  CHECK(nme.getPosition() == coordinates_);
}

TEST_CASE("handleCollision()")
{
  DataHandler dh("../TowerDefence/config/config.json");
  nlohmann::json config;
  nlohmann::json config_b;
  nlohmann::json config_p;
  config = dh.getConfig()["game_entity"]["enemy"]["covid"]["parameters"]["1"];
  config_b = dh.getConfig()["game_entity"]["base"]["parameters"];
  config_p = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
  sf::Texture test_texture;
  std::vector<sf::Texture *> texture;
  texture.push_back(&test_texture);

  sf::Vector2f coordinates (1,1);
  sf::Vector2f coordinates2 (4,1);
  std::vector<sf::Vector2f> road_vector;
  road_vector.push_back(coordinates);
  road_vector.push_back(coordinates2);

  Enemy nme(1.0, 1.0, texture, config, &road_vector);  
  Base * base_ptr{new Base(0.0, 0.0, texture, config_b)};
  Spit * proj_ptr{new Spit(1, 1, texture, config_p, 1, 1)};

  int e_start_hp{config["hp"]};

  nme.handleCollision(proj_ptr);
  CHECK(proj_ptr->isDestroyed());
  CHECK(nme.getHp() == e_start_hp - proj_ptr->getDamage());
  CHECK_FALSE(nme.isDestroyed());
  nme.handleCollision(proj_ptr);
  nme.updateObject();
  CHECK(nme.isDestroyed()); //Enemeis have 2 hp on level 1.
  delete proj_ptr;

  Enemy nme_2(1.0, 1.0, texture, config, &road_vector);
  int b_start_hp{base_ptr->getLife()};

  CHECK_FALSE(nme_2.isDestroyed());

  nme_2.handleCollision(base_ptr);

  CHECK(base_ptr->getLife() == b_start_hp - nme_2.getDamage());

  CHECK(nme_2.isDestroyed());
  
  delete base_ptr;
}
