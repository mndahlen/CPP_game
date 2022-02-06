#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "../GameObject/DynamicObject/DynamicTower/FighterjetTower.hpp"
#include "../GameObject/DynamicObject/Enemy/Enemy.hpp"
#include "../GameObject/DynamicObject/Projectile/Spit.hpp"
#include "../GameObject/DynamicObject/MoneyBag.hpp"
#include "../GameObject/DynamicObject/PlayerFigure.hpp"
#include "../GameObject/StaticObject/Base/Base.hpp"
#include "../GameObject/StaticObject/PlayingField/PlayingField.hpp"
#include "../GameObject/StaticObject/Square/RoadSquare.hpp"
#include "../GameObject/StaticObject/Square/TowerSquare.hpp"
#include "../GameObject/StaticObject/StaticTower/HandSanitizerTower.hpp"
#include "../Menu/Menu.hpp"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


/*

    Internal States     ID
--------------------------------------

- PrepState         0
- RunState          1
- BuildState        2

--------------------------------------

**/


class GameState : public State
{
    public:
        GameState(sf::RenderWindow * window, DataHandler * datahandler,
                  std::map<std::string, sf::Texture*> * texture_map_ptr,
                  std::map<std::string, sf::Font*> * font_map_ptr);
        ~GameState();

        void updateState() override;
        void render() override;

    private:
        sf::Clock clock{};
        sf::Time last_spawn_time{};
        sf::Time moneybag_last_spawn_time{};
        sf::Sprite fighterjet_sprite{};
        sf::Sprite handsanitizer_sprite{};

        int score{0};

        int level{1};
        int internal_state{0};
        int buy_option_select{0};
        int enemy_amount{};
        int currently_placing_tower{0};
        float enemy_spawn_time{};
        float moneybag_spawn_time{};


        Menu * run_menu{};
        Menu * prep_menu{};
        Menu * current_menu{};
        PlayingField * playingfield{};
        PlayerFigure * playerfigure{};
        Button * leveldisplay{};
        Button * moneydisplay{};
        Button * hpdisplay{};
        Base * base{};
        std::vector<Enemy *> enemies{};
        std::vector<StaticTower *> static_towers{};
        std::vector<DynamicTower *> dynamic_towers{};
        std::vector<Projectile *> projectiles{};
        std::vector<MoneyBag *> moneybags{};

        std::vector<sf::Vector2f> enemy_path{};

        void initGameState();
        void initRunMenu();
        void initPrepMenu();
        void initPlayingfield();
        void initBase();
        void initPlayerfigure();
        void initButtons();
        void initSprites();


        void handlePrepState();
        void handleRunState();
        void handleBuyState();

        void getLevelParameters();
        void updateObjects();
        void updateButtons();
        void checkEnemyCollisions(Enemy * enemy);
        void checkPlayerFigureCollisions(PlayerFigure * playerfigure);

        void enemySpawner();
        void moneybagSpawner();
        void buyFighterjet();
        void buyHandsanitizer();
        sf::Vector2f getClosestPlayfieldPosition(int x, int y);
        std::vector<sf::Texture*> getTextures(std::vector<std::string> texture_names);

        int getLevelScore();
};

#endif
