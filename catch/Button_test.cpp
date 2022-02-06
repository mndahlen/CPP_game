#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/Button/Button.cpp"

TEST_CASE("Button initialization")
{
    std::string MEDIADIR3 = "../TowerDefence/media_files";
    try
    {   
        sf::Texture texture;
        texture.loadFromFile(MEDIADIR3 + "/png_images/button.png");
        sf::Font font;
        font.loadFromFile(MEDIADIR3 + "/fonts/arial.ttf");
        Button button(0,0,100,40,&texture,"Ay lmao",&font);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }
}

TEST_CASE("get/set position")
{
    std::string MEDIADIR3 = "../TowerDefence/media_files";   
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR3 + "/png_images/button.png");
    sf::Font font;
    font.loadFromFile(MEDIADIR3 + "/fonts/arial.ttf");
    Button button(0,0,100,40,&texture,"Ay lmao",&font);


    CHECK(button.getPosition() == sf::Vector2f{0,0});

    button.setPosition(10,10);
    CHECK(button.getPosition() == sf::Vector2f{10,10});

    button.setPosition(-10,10);
    CHECK(button.getPosition() == sf::Vector2f{-10,10});

    button.setPosition(-10,-10);
    CHECK(button.getPosition() == sf::Vector2f{-10,-10});

    button.setPosition(10,-10);
    CHECK(button.getPosition() == sf::Vector2f{10,-10});

    button.setPosition(-12,10);
    CHECK(button.getPosition() == sf::Vector2f{-12,10});

    button.setPosition(0,0);
    CHECK(button.getPosition() == sf::Vector2f{0,0});

    button.setPosition(115241,10123);
    CHECK(button.getPosition() == sf::Vector2f{115241,10123});
}

TEST_CASE("mouseOnButton()")
{
    std::string MEDIADIR3 = "../TowerDefence/media_files";    
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR3 + "/png_images/button.png");
    sf::Font font;
    font.loadFromFile(MEDIADIR3 + "/fonts/arial.ttf");
    Button button(0,0,100,40,&texture,"Ay lmao",&font);

    int x{0}, y{0};
    CHECK(button.mouseOnButton(x,y) == true);

    x = 200, y = 200;
    CHECK(button.mouseOnButton(x,y) == false);


    Button button2(100,100,50,50,&texture,"yeet",&font);

    x = 200, y = 200;
    CHECK(button2.mouseOnButton(x,y) == false);

    x = 100, y = 100;
    CHECK(button2.mouseOnButton(x,y) == true);
}
