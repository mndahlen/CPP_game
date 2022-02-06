#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/GameObject/DynamicObject/MoneyBag.hpp"
#include "../TowerDefence/GameObject/DynamicObject/PlayerFigure.hpp"
#include "../TowerDefence/DataHandler/DataHandler.hpp"

TEST_CASE("MoneyBag initialization")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    nlohmann::json config_b;
    config = dh.getConfig()["game_entity"]["moneybag"]["parameters"];
    config_b = dh.getConfig()["game_entity"]["base"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    try
    {
        Base basse(0, 0, texture, config_b);
        MoneyBag mb(0, 0, 1, texture, config, &basse);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }

}

TEST_CASE("updateObject()")
{
    // sf::Texture texture;
    // Base basse(0, 0, &texture);
    // float x_pos{0};
    // float y_pos{0};
    // float direction{1};
    // float speed{1};
    // MoneyBag mb(x_pos, y_pos, direction, speed, &texture, &basse);

    // mb.updateObject();

    // sf::Vector2f new_pos{mb.getPosition()};

    // CHECK(std::abs(x_pos - new_pos.x) < 1e-5);
    // CHECK(std::abs(y_pos + direction*speed - new_pos.y) < 1e-5);
}

TEST_CASE("Check if MoneyBag is destoyed if outside screen")
{
//   sf::Texture texture;
//   Base basse(0, 0, &texture);
//   float x_pos{100};
//   float y_pos1{0};
//   float y_pos2{700};
//   float y_pos3{701};
//   float direction{1};
//   float speed{1};

//   MoneyBag * mb1{new MoneyBag(x_pos, y_pos1, direction, speed, &texture, &basse)};
//   MoneyBag * mb2{new MoneyBag(x_pos, y_pos2, direction, speed, &texture, &basse)};
//   MoneyBag * mb3{new MoneyBag(x_pos, y_pos3, direction, speed, &texture, &basse)};

//   mb1->updateObject();
//   mb2->updateObject();
//   mb3->updateObject();

//   CHECK_FALSE(mb1->isDestroyed());
//   CHECK_FALSE(mb2->isDestroyed());
//   CHECK(mb3->isDestroyed());
}

TEST_CASE("destroy()")
{
    // sf::Texture texture;
    // Base basse(0, 0, &texture);
    // float x_pos{0};
    // float y_pos{0};
    // float direction{1};
    // float speed{1};
    // MoneyBag * mb{new MoneyBag(x_pos, y_pos, direction, speed, &texture, &basse)};

    // CHECK_FALSE(mb->isDestroyed());

    // mb->destroy();

    // CHECK(mb->isDestroyed());

}

TEST_CASE("handleCollison()")
{
    // sf::Texture texture;
    // Base basse(0, 0, &texture);
    // std::string test_string;
    // float x_pos{0};
    // float y_pos{0};
    // float direction{1};
    // float speed{1};
    // MoneyBag mb(x_pos, y_pos, direction, speed, &texture, &basse);
    // MoneyBag * mb2{new MoneyBag(x_pos, y_pos, direction, speed, &texture, &basse)};

    // mb.handleCollision(mb2);

    // CHECK_FALSE(mb.isDestroyed());

    // delete mb2;

    // PlayerFigure * pf_ptr{new PlayerFigure(0, 0, &texture, 1)};

    // CHECK(basse.getMoney() == 200);

    // mb.handleCollision(pf_ptr);

    // CHECK(mb.isDestroyed());
    // CHECK(basse.getMoney() == 201);


    // delete pf_ptr;
}
