#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/GameObject/DynamicObject/Projectile/Spit.hpp"
#include "../TowerDefence/DataHandler/DataHandler.hpp"

TEST_CASE("Spit initialization")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    try
    {
        Spit spit_proj(0, 0, texture, config, 1, 1);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }
}

TEST_CASE("getSpeed() should return the speed")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    float speed{config["speed"]};

    Spit spit_proj(0, 0, texture, config, 1, 1);

    CHECK(std::abs(spit_proj.getSpeed() - speed) < 1e-5);
}

TEST_CASE("getDamage() should return the damage")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    float damage{config["damage"]};

    Spit spit_proj(0, 0, texture, config, 1, 1);

    CHECK(std::abs(spit_proj.getDamage() - damage) < 1e-5);
}

TEST_CASE("updateObject() should move the projectile forward one step (with the speed)")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    float x_pos{0};
    float y_pos{0};
    float x_dir{1};
    float y_dir{0};
    float speed{config["speed"]};

    Spit spit_proj(x_pos, y_pos, texture, config, x_dir, y_dir);

    spit_proj.updateObject();

    sf::Vector2f new_pos{spit_proj.getPosition()};

    CHECK(std::abs(x_pos + x_dir*speed - new_pos.x) < 1e-5);
    CHECK(std::abs(y_pos + y_dir*speed - new_pos.y) < 1e-5);
}

TEST_CASE("updateObject(), direction vector should be normal")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    float x_pos{0};
    float y_pos{0};
    float x_dir{3};
    float y_dir{4};
    float speed{config["speed"]};
    float damage{config["damage"]};
    float normal{std::sqrt(std::pow(x_dir, 2) + std::pow(y_dir, 2))};

    Spit spit_proj(x_pos, y_pos, texture, config, x_dir, y_dir);

    spit_proj.updateObject();

    sf::Vector2f new_pos{spit_proj.getPosition()};

    CHECK(std::abs(x_pos + x_dir*speed/normal - new_pos.x) < 1e-5);
    CHECK(std::abs(y_pos + y_dir*speed/normal - new_pos.y) < 1e-5);
}

TEST_CASE("destroy() should make projectile inactive (destroyed)")
{
    DataHandler dh("../TowerDefence/config/config.json");
    nlohmann::json config;
    config = dh.getConfig()["game_entity"]["projectile"]["spit"]["parameters"];
    sf::Texture test_texture;
    std::vector<sf::Texture *> texture;
    texture.push_back(&test_texture);

    float x_pos{0};
    float y_pos{0};
    float x_dir{3};
    float y_dir{4};
    float speed{config["speed"]};
    float damage{config["damage"]};

    Spit * spit_proj{new Spit(x_pos, y_pos, texture, config, x_dir, y_dir)};

    CHECK_FALSE(spit_proj->isDestroyed());

    spit_proj->destroy();

    CHECK(spit_proj->isDestroyed());

}

