#ifndef PLAYINGFIELD_HPP
#define PLAYINGFIELD_HPP

#include "../StaticObject.hpp"
#include "../Square/TowerSquare.hpp"
#include "../Square/RoadSquare.hpp"
#include "../Square/Square.hpp"
#include <iostream>

class PlayingField : public StaticObject
{
    public:
        PlayingField(float pos_x, float pos_y, 
                    std::vector<sf::Texture*> textures_, 
                    std::vector<std::vector<int>> grid_);
        ~PlayingField();

        void switchOccupied(int x, int y);
        bool isOccupied(int x, int y);
        std::vector<int> getSquareIndex(int x, int y);
        std::vector<int> getRoadStartIndex();
        std::vector<int> getRoadEndIndex();
        std::vector<sf::Vector2f> getEnemyPath();
        sf::Vector2f getSquareMiddle(int x, int y);

        void render(sf::RenderWindow * window_ptr) override;
        void handleCollision(GameObject * collision_object) override;
        void updateObject() override;  

    private:
        std::vector<Square *> squares;
        std::vector<sf::Texture*> textures;
        std::vector<int> road_start_index;
        std::vector<int> road_end_index;
        std::vector<std::vector<int>> grid;
        std::vector<sf::Vector2f> enemy_path;

        void initEnemyPath();
        void initSquares();
};

#endif
