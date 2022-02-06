#include "../TowerDefence/DataHandler/DataHandler.hpp"
#include "../TowerDefence/GameObject/DynamicObject/DynamicTower/FighterjetTower.hpp"
#include "catch_files/catch.hpp"

TEST_CASE("FighterjetTower init")
{   
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    nlohmann::json config_p;
    config = dh.getConfig()["game_entity"]["dynamictower"]["fighterjet"]["parameters"];
    config_p = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);
    std::vector <Projectile*> proj_vect;

    try
    {
      FighterjetTower test_fj{1, 1, texture, config, &proj_vect, config_p};
      SUCCEED();
    }
    catch(const std::exception& e)
    {
      FAIL();
    }
}

// TEST_CASE("FighterjetTower updateObject")
// {
//     DataHandler dh("../TowerDefence/config/config.json");
//     nlohmann::json config;
//     nlohmann::json config_p;
//     config = dh.getConfig()["game_entity"]["dynamictower"]["fighterjet"]["parameters"];
//     config_p = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
//     sf::Texture test_texture;
//     std::vector<sf::Texture *> texture;
//     texture.push_back(&test_texture);
//     std::vector <Projectile*> proj_vect;

//     FighterjetTower test_fj{1, 1, texture, config, &proj_vect, config_p};

//     CHECK(test_fj.getCountdown() == 1);
//     CHECK(proj_vect.empty());

//     test_fj.updateObject();
//     CHECK(test_fj.getCountdown() == 240);
//     CHECK_FALSE(proj_vect.empty());

//     test_fj.updateObject();
//     CHECK(test_fj.getCountdown() == 239);
//     CHECK(test_fj.getXdir() == -1);
//     CHECK(test_fj.getYdir() == 1);

//     for (int i = 0; i < 59; i++) {
//       test_fj.updateObject();
//     };

//     CHECK(test_fj.getCountdown() == 180);
//     CHECK(test_fj.getXdir() == -1);
//     CHECK(test_fj.getYdir() == -1);
//     CHECK(proj_vect.size() == 2);

//     for (int i = 0; i < 60; i++) {
//       test_fj.updateObject();
//     };

//     CHECK(test_fj.getCountdown() == 120);
//     CHECK(test_fj.getXdir() == 1);
//     CHECK(test_fj.getYdir() == -1);

//     for (int i = 0; i < 60; i++) {
//       test_fj.updateObject();
//     };

//     CHECK(test_fj.getCountdown() == 60);
//     CHECK(test_fj.getXdir() == 1);
//     CHECK(test_fj.getYdir() == 1);

//     for (int i = 0; i < 60; i++) {
//       test_fj.updateObject();
//     };

//     CHECK(test_fj.getCountdown() == 240);
//     CHECK(test_fj.getXdir() == -1);
//     CHECK(test_fj.getYdir() == 1);

// }
