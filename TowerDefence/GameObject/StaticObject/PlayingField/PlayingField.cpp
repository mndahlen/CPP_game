#include "PlayingField.hpp"

PlayingField::PlayingField(float pos_x, float pos_y,
                           std::vector<sf::Texture*> textures_,
                           std::vector<std::vector<int>> grid_)
                           :
                           StaticObject(pos_x, pos_y, textures_[0]),
                           textures{textures_}, grid{grid_}
{
    sprite.scale(1,1);
    sprite.setOrigin(0,0);
    initSquares();
    initEnemyPath();
}

PlayingField::~PlayingField()
{
}

void PlayingField::initEnemyPath()
{
    std::vector<int> start_index = getRoadStartIndex();
    std::vector<int> index{start_index};
    std::vector<int> last_index{index};
    sf::Vector2f test = getSquareMiddle(index.at(1), index.at(0));
    enemy_path.push_back(getSquareMiddle(index.at(1), index.at(0)));
    int current_value{0};

    while (current_value != 3)
    {
        for (int r = -1; r < 2; r++)
        {
            for (int c = -1; c < 2; c++)
            {
                if ((r == 0 || c == 0) && !(r == c))
                {
                    std::vector<int> new_index{index[0]+r,index[1]+c};

                    if (new_index[0] > 0 && new_index[1] > 0)
                    {
                        current_value = grid[new_index[0]][new_index[1]];
                        if (current_value == 1 || current_value == 3)
                        {
                            if (!(last_index == new_index))
                            {
                                last_index = index;
                                index = new_index;
                                enemy_path.push_back(getSquareMiddle(35*index[1], 35*index[0]));
                                //Break FOR but not WHILE
                                r = 1;
                                c = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PlayingField::initSquares()
{
    sf::Texture * road_texture = textures[1];
    sf::Texture * grass_texture = textures[2];

    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            int grid_value = grid[row][col];

            if (grid_value == 0)
            {
                /* TowerSquare */
                Square * square
                {
                    new TowerSquare(col*35, 
                                    row*35, 
                                    grass_texture)
                };

                squares.push_back(square);
            }
            else
            {
                /* RoadSquare */
                Square * square
                {
                    new RoadSquare(col*35, 
                                   row*35, 
                                   road_texture)
                };

                squares.push_back(square);

                if (grid_value == 2)
                {
                    road_start_index.push_back(row);
                    road_start_index.push_back(col);
                }
                else if (grid_value == 3)
                {
                    road_end_index.push_back(row);
                    road_end_index.push_back(col);
                }
            }
        }
    }
}

std::vector<sf::Vector2f> PlayingField::getEnemyPath()
{
    return enemy_path;
}

std::vector<int> PlayingField::getSquareIndex(int x, int y)
{
    if (x < 700 && y < 700)
    {
        int row = std::floor(y/35);
        int col = std::floor(x/35);
        std::vector<int> index{row,col};

        return index;
    }
    else
    {
        int row{-1};
        int col{-1};
        std::vector<int> index{row,col};

        return index;
    }
}

sf::Vector2f PlayingField::getSquareMiddle(int x, int y)
{
    int x_middle = std::floor(x/35)*35 + 35/2;
    int y_middle = std::floor(y/35)*35 + 35/2;
    sf::Vector2f square_middle{x_middle,y_middle};
    return square_middle;
}

bool PlayingField::isOccupied(int x, int y)
{
    std::vector<int> square_index = getSquareIndex(x,y);
    int row{square_index[0]};
    int col{square_index[1]};

    return squares[row*20 + col]->isOccupied();
}

void PlayingField::switchOccupied(int x, int y)
{
    std::vector<int> square_index = getSquareIndex(x,y);
    int row{square_index[0]};
    int col{square_index[1]};

    squares[row*20 + col]->switchOccupied();
}

void PlayingField::handleCollision(GameObject * collision_object){}

void PlayingField::updateObject(){}

void PlayingField::render(sf::RenderWindow * window)
{
    window->draw(sprite);


    for (std::vector<Square *>::iterator it = squares.begin();
                                       it != squares.end();
                                       ++it)
    {
        (*it)->render(window);
    }
}

std::vector<int> PlayingField::getRoadStartIndex()
{
    return road_start_index;
}

std::vector<int> PlayingField::getRoadEndIndex()
{
    return road_end_index;
}
