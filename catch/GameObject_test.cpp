#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/GameObject/TestObject.cpp"
#include <SFML/Graphics.hpp>

TEST_CASE("GameObject initialization")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    try
    {
        sf::Texture texture;
        texture.loadFromFile(MEDIADIR + "road_straight.png");
        TestObject test(0, 0, &texture);
        SUCCEED();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        FAIL();
    }
}

TEST_CASE("Collision true")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");

    TestObject object1(0, 0, &texture);
    TestObject object2(0, 0, &texture);

    CHECK(object1.checkCollision(&object2) == true);

    CHECK(object1.checkCollision(&object2) == true);

    TestObject object3(0, 0, &texture);
    TestObject object4(34, 0, &texture);

    CHECK(object3.checkCollision(&object4) == true);

    TestObject object5(0, 0, &texture);
    TestObject object6(-30, 0, &texture);

    CHECK(object5.checkCollision(&object6) == true);

    TestObject object7(0, 0, &texture);
    TestObject object8(0, 32, &texture);

    CHECK(object7.checkCollision(&object8) == true);

    TestObject object9(0, 0, &texture);
    TestObject object10(0, -33, &texture);

    CHECK(object9.checkCollision(&object10) == true);

    TestObject object11(53, 2, &texture);
    TestObject object12(53 + 15, 2 - 25, &texture);

    CHECK(object11.checkCollision(&object12) == true);

    TestObject object13(53, 2, &texture);
    TestObject object14(53, 2, &texture);

    CHECK(object13.checkCollision(&object14) == true);
}

TEST_CASE("Collision false")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");
    TestObject object1(100, 100, &texture);
    TestObject object2(0, 0, &texture);

    CHECK(object1.checkCollision(&object2) == false);

    TestObject object3(0, 0, &texture);
    TestObject object4(35, 0, &texture);

    CHECK(object3.checkCollision(&object4) == false);

    TestObject object5(0, 0, &texture);
    TestObject object6(-35, 0, &texture);

    CHECK(object5.checkCollision(&object6) == false);

    TestObject object7(0, 0, &texture);
    TestObject object8(0, 35, &texture);

    CHECK(object7.checkCollision(&object8) == false);

    TestObject object9(0, 0, &texture);
    TestObject object10(0, -35, &texture);

    CHECK(object9.checkCollision(&object10) == false);

    TestObject object11(53, 2, &texture);
    TestObject object12(53 + 35, 2 - 35, &texture);

    CHECK(object11.checkCollision(&object12) == false);
}

TEST_CASE("Position get/set")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");

    sf::Vector2f v0(0,0);
    TestObject object1(0, 0, &texture);
    CHECK(object1.getPosition() == v0);

    sf::Vector2f v1(10,10);
    object1.setPosition(10,10);
    CHECK(object1.getPosition() == v1);

    sf::Vector2f v2(-10,10);
    object1.setPosition(-10,10);
    CHECK(object1.getPosition() == v2);

    sf::Vector2f v3(10,-10);
    object1.setPosition(10,-10);
    CHECK(object1.getPosition() == v3);
}

TEST_CASE("Rotation get/set")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");
    TestObject object1(0, 0, &texture);

    CHECK(object1.getRotation() == 0);

    object1.setRotation(10);
    CHECK((object1.getRotation() == 0) == false);
    CHECK(object1.getRotation() == 10);

    object1.setRotation(0);
    object1.setRotation(-1231451);
    CHECK(object1.getRotation() == 360 - 1231451%360);
}

TEST_CASE("rotate()")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");
    TestObject object1(0, 0, &texture);

    CHECK(object1.getRotation() == 0);

    object1.rotate(100);
    CHECK(object1.getRotation() == 100);

    object1.rotate(-100);
    CHECK(object1.getRotation() == 0);

    object1.rotate(-50);
    CHECK(object1.getRotation() == 310);
}

TEST_CASE("move()")
{
    std::string MEDIADIR = "../TowerDefence/media_files/png_images/";
    sf::Texture texture;
    texture.loadFromFile(MEDIADIR + "road_straight.png");
    TestObject object1(0, 0, &texture);

    sf::Vector2f v0(0,0);
    CHECK(object1.getPosition() == v0);

    sf::Vector2f v1(5,3);
    object1.move(5,3);
    CHECK(object1.getPosition() == v1);

    object1.move(-5,-3);
    CHECK(object1.getPosition() == v0);

    sf::Vector2f v3(-1231,-53512);
    object1.move(-1231,-53512);
    CHECK(object1.getPosition() == v3);
}
