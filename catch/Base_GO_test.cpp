#include "catch_files/catch.hpp"
#include <iostream>
#include <vector>
#include "../TowerDefence/GameObject/StaticObject/Base/Base.hpp"
#include "../TowerDefence/GameObject/DynamicObject/Enemy/Enemy.hpp"
#include "../TowerDefence/DataHandler/DataHandler.hpp"



TEST_CASE("Base initialziesaition")
{
    
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    try
    {   
        Base base_player(0.0, 0.0, texture, config);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }
}

TEST_CASE("getMoney() should give the amount of money base has")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    int money{config["money"]};
    Base base_player(0.0, 0.0, texture, config);

    CHECK(money == base_player.getMoney());
}

TEST_CASE("getLife() should give the amount of life base has")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    int life{config["life"]};
    Base base_player(0.0, 0.0, texture, config);

    CHECK(life == base_player.getLife());
}

TEST_CASE("addMoney() should add money to the base")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    int money_to_add{20};
    int money{config["money"]};
    Base base_player(0.0, 0.0, texture, config);

    base_player.addMoney(money_to_add);

    CHECK(money_to_add + money == base_player.getMoney());
}

TEST_CASE("spendMoney should reduce the amount of money in base")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    int cost{56};
    int money{config["money"]};
    Base base_player(0.0, 0.0, texture, config);

    base_player.spendMoney(cost);

    CHECK(money - cost == base_player.getMoney());
}

TEST_CASE("takeDamage should reduce the amount of life in base")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    int dmg{31};
    int life{config["life"]};
    Base base_player(0.0, 0.0, texture, config);

    base_player.takeDamage(dmg);

    CHECK(life - dmg == base_player.getLife());
}
