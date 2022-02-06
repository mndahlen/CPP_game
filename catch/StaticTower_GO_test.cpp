#include "../TowerDefence/GameObject/StaticObject/StaticTower/HandSanitizerTower.hpp"
#include "catch_files/catch.hpp"

//std::string MEDIADIR = "../TowerDefence/media_files/png_images/";

TEST_CASE("StaticTower")
{
    // sf::Texture texture;
    // std::vector <Projectile*> proj_vect;
    // std::vector <Projectile*> * proj_vect_ptr{new std::vector <Projectile*>()};
    // * proj_vect_ptr = proj_vect;
    // HandSanitizerTower test_h_s{1,1,&texture, proj_vect_ptr};
    // CHECK(test_h_s.getDescription() == "The Hand sanitizer tower is placed on a tower square.\nShooting hand sanitizer at the closest virus it tries to end the pandemic.\nRange: \nDamage: \nCost: ");
    // CHECK(test_h_s.getDamage() == 1);
    // CHECK(test_h_s.getCost() == 1);
    // CHECK(test_h_s.getDetectionRange() == 1);
}

TEST_CASE("HandSanitizerTower")
{
  // sf::Texture texture;
  // sf::Vector2i coordinates (2,2);
  // std::vector<sf::Vector2i> road_vector;
  // road_vector.push_back(coordinates);
  // std::vector<sf::Vector2i> * road_vector_ptr{new std::vector<sf::Vector2i>()};
  // *road_vector_ptr = road_vector;

  // std::vector <Projectile*> proj_vect;

  // HandSanitizerTower test_h_s(1,1,&texture, &proj_vect);
  // Enemy * col_obj{new Enemy(1,1,&texture, 1, 1, 1, road_vector_ptr)};
  // CHECK(test_h_s.getCooldown() == 0);
  // CHECK(proj_vect.empty());
  // test_h_s.handleCollision(col_obj);
  // CHECK(proj_vect.size() == 1);
  // CHECK(test_h_s.getCooldown() == 10);
  // test_h_s.updateObject();
  // CHECK(test_h_s.getCooldown() == 9);
  // test_h_s.handleCollision(col_obj);
  // CHECK(proj_vect.size() == 1);
  // CHECK_FALSE(test_h_s.getCooldown() == 10);

  // delete col_obj;
  // delete road_vector_ptr;
}
