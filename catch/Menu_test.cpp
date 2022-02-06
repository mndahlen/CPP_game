#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/Menu/Menu.cpp"

TEST_CASE("Menu initialization")
{
    std::string MEDIADIR4 = "../TowerDefence/media_files";
    try
    {    
        sf::Texture menu_texture{};
        sf::Texture button_texture{};
        sf::Font font;
        menu_texture.loadFromFile(MEDIADIR4 + "/png_images/menu.png");
        button_texture.loadFromFile(MEDIADIR4 + "/png_images/button.png");
        font.loadFromFile(MEDIADIR4 + "/fonts/arial.ttf");
        
        Menu menu(200,350,200,700,&menu_texture);
        menu.addButton(0,0,100,30, &button_texture, "test", &font);
        menu.addButton(0,50,100,30, &button_texture, "test2", &font);
        menu.addButton(0,300,150,30, &button_texture, "new character", &font);

        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }
}

TEST_CASE("get//set position")
{   
    std::string MEDIADIR4 = "../TowerDefence/media_files"; 
    sf::Texture menu_texture{};
    menu_texture.loadFromFile(MEDIADIR4 + "/png_images/menu.png");
    Menu menu(0,0,200,700,&menu_texture);


    CHECK(menu.getPosition() == sf::Vector2f{0,0});

    menu.setPosition(10,10);
    CHECK(menu.getPosition() == sf::Vector2f{10,10});

    menu.setPosition(-10,10);
    CHECK(menu.getPosition() == sf::Vector2f{-10,10});

    menu.setPosition(-10,-10);
    CHECK(menu.getPosition() == sf::Vector2f{-10,-10});

    menu.setPosition(10,-10);
    CHECK(menu.getPosition() == sf::Vector2f{10,-10});

    menu.setPosition(-12,10);
    CHECK(menu.getPosition() == sf::Vector2f{-12,10});

    menu.setPosition(0,0);
    CHECK(menu.getPosition() == sf::Vector2f{0,0});

    menu.setPosition(115241,10123);
    CHECK(menu.getPosition() == sf::Vector2f{115241,10123});
}


TEST_CASE("getSelectedOption()")
{    
    std::string MEDIADIR4 = "../TowerDefence/media_files";
    sf::Texture menu_texture{};
    sf::Texture button_texture{};
    sf::Font font;
    menu_texture.loadFromFile(MEDIADIR4 + "/png_images/menu.png");
    button_texture.loadFromFile(MEDIADIR4 + "/png_images/button.png");
    font.loadFromFile(MEDIADIR4 + "/fonts/arial.ttf");

    Menu menu(200,350,200,700,&menu_texture);
    menu.addButton(0,0,100,30, &button_texture, "button1", &font);
    menu.addButton(0,50,100,30, &button_texture, "button2", &font);
    menu.addButton(0,300,150,30, &button_texture, "button3", &font);
    menu.addButton(0,-300,150,30, &button_texture, "button4", &font);
    menu.addButton(100,-250,150,30, &button_texture, "button5", &font);
    menu.addButton(0,-200,70,70, &button_texture, "thicc", &font);

    int x{200 + 0}, y{350 + 0};
    CHECK(menu.getSelectedOption(x, y) == 1);

    x = 200 + 1000, y = 350 + 1000;
    CHECK(menu.getSelectedOption(x, y) == 0);

    x = 200 + 0, y = 350 + 50;
    CHECK(menu.getSelectedOption(x, y) == 2);

    x = 200 + 0, y = 350 + 300;
    CHECK(menu.getSelectedOption(x, y) == 3);

    x = 200 + 0, y = 350 -300;
    CHECK(menu.getSelectedOption(x, y) == 4);

    x = 200 + 100, y = 350 - 250;
    CHECK(menu.getSelectedOption(x, y) == 5);

    x = 200 + 0, y = 350 - 200;
    CHECK(menu.getSelectedOption(x, y) == 6);
}

TEST_CASE("getSelectedOption() after changed position")
{    
    std::string MEDIADIR4 = "../TowerDefence/media_files";
    sf::Texture menu_texture{};
    sf::Texture button_texture{};
    sf::Font font;
    menu_texture.loadFromFile(MEDIADIR4 + "/png_images/menu.png");
    button_texture.loadFromFile(MEDIADIR4 + "/png_images/button.png");
    font.loadFromFile(MEDIADIR4 + "/fonts/arial.ttf");

    Menu menu(200,350,200,700,&menu_texture);
    menu.addButton(0,0,100,30, &button_texture, "button1", &font);
    menu.addButton(0,50,100,30, &button_texture, "button2", &font);
    menu.addButton(0,300,150,30, &button_texture, "button3", &font);
    menu.addButton(0,-300,150,30, &button_texture, "button4", &font);
    menu.addButton(100,-250,150,30, &button_texture, "button5", &font);
    menu.addButton(0,-200,70,70, &button_texture, "thicc", &font);

    menu.setPosition(500,500);

    int x{500 + 0}, y{500 + 0};
    CHECK(menu.getSelectedOption(x, y) == 1);

    x = 500 + 1000, y = 500 + 1000;
    CHECK(menu.getSelectedOption(x, y) == 0);

    x = 500 + 0, y = 500 + 50;
    CHECK(menu.getSelectedOption(x, y) == 2);

    x = 500 + 0, y = 500 + 300;
    CHECK(menu.getSelectedOption(x, y) == 3);

    x = 500 + 0, y = 500 -300;
    CHECK(menu.getSelectedOption(x, y) == 4);

    x = 500 + 100, y = 500 - 250;
    CHECK(menu.getSelectedOption(x, y) == 5);

    x = 500 + 0, y = 500 - 200;
    CHECK(menu.getSelectedOption(x, y) == 6);
}