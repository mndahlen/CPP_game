#include "GameState.hpp"

GameState::GameState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr)
                               :
                               State(window,datahandler,texture_map_ptr,font_map_ptr,1)
{
    initGameState();
}

GameState::~GameState()
{
}

void GameState::updateState()
{
    switch (internal_state)
    {
    case 0:
        handlePrepState();
        break;

    case 1: // Runstate
        handleRunState();
        break;

    case 2: //build
        handleBuyState();
        break;
    }

    updateObjects();
}

void GameState::render()
{
    playingfield->render(window);
    base->render(window);

    for (int i = 0; i < static_towers.size(); i++)
    {
        (static_towers.at(i))->render(window);
    }
    playerfigure->render(window);

    if (internal_state == 1)
    {
        for (std::vector<Enemy *>::iterator it = enemies.begin();
                                        it != enemies.end();
                                        ++it)
        {
            (*it)->render(window);
        }

        for (std::vector<MoneyBag *>::iterator it = moneybags.begin();
                                    it != moneybags.end();
                                    ++it)
        {
            (*it)->render(window);
        }

        for (std::vector<Projectile *>::iterator it = projectiles.begin();
                                    it != projectiles.end();
                                    ++it)
        {
            (*it)->render(window);
        }

    }

    for (std::vector<DynamicTower *>::iterator it = dynamic_towers.begin();
                                it != dynamic_towers.end();
                                ++it)
    {
        (*it)->render(window);
    }

    current_menu->render(window);

    leveldisplay->render(window);
    moneydisplay->render(window);
    hpdisplay->render(window);

    if (currently_placing_tower == 1)
    {
        auto mouse_pos = sf::Mouse::getPosition(*window);
        fighterjet_sprite.setPosition(mouse_pos.x, mouse_pos.y);
        window->draw(fighterjet_sprite);
    }

    if (currently_placing_tower == 2)
    {
        auto mouse_pos = sf::Mouse::getPosition(*window);
        handsanitizer_sprite.setPosition(mouse_pos.x, mouse_pos.y);
        window->draw(handsanitizer_sprite);
    }
}


void GameState::initGameState()
{
    initRunMenu();
    initPrepMenu();
    initPlayingfield();
    initPlayerfigure();
    initBase();
    initButtons();
    initSprites();

    /* Load parameters for first level */
    getLevelParameters();
}

void GameState::initRunMenu()
{
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button_unclickable");
    sf::Font * font = font_map->at("arial");
    run_menu = new Menu(800,350,200,700, menu_texture);

    int fighter_prize = (datahandler->getConfig())["game_entity"]
                                                  ["dynamictower"]
                                                  ["fighterjet"]
                                                  ["parameters"]
                                                  ["cost"];
    int sanitizer_prize = (datahandler->getConfig())["game_entity"]
                                                    ["statictower"]
                                                    ["handsanitizer"]
                                                    ["parameters"]
                                                    ["cost"];
    std::string fighter_button_str = "fighterjet: " + std::to_string(fighter_prize) + "$";
    std::string sanitizer_button_str = "handsanitizer: " + std::to_string(sanitizer_prize) + "$";

    run_menu->addButton(100,25,150,40,  button_texture, "Start Level", font);
    run_menu->addButton(100,100,150,40,  button_texture, fighter_button_str, font);
    run_menu->addButton(100,175,150,40,  button_texture, sanitizer_button_str, font);
}

void GameState::initPrepMenu()
{
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button");
    sf::Font * font = font_map->at("arial");
    prep_menu = new Menu(800,350,200,700, menu_texture);

    int fighter_prize = (datahandler->getConfig())["game_entity"]
                                                  ["dynamictower"]
                                                  ["fighterjet"]
                                                  ["parameters"]
                                                  ["cost"];
    int sanitizer_prize = (datahandler->getConfig())["game_entity"]
                                                    ["statictower"]
                                                    ["handsanitizer"]
                                                    ["parameters"]
                                                    ["cost"];
    std::string fighter_button_str = "fighterjet: " + std::to_string(fighter_prize) + "$";
    std::string sanitizer_button_str = "handsanitizer: " + std::to_string(sanitizer_prize) + "$";

    prep_menu->addButton(100,25,150,40,  button_texture, "Start Level", font);
    prep_menu->addButton(100,100,150,40,  button_texture, fighter_button_str, font);
    prep_menu->addButton(100,175,150,40,  button_texture, sanitizer_button_str, font);
}

void GameState::initPlayingfield()
{
    nlohmann::json config;
    config = (datahandler->getConfig())["game_entity"]["playingfield"];
    std::vector<std::string> texture_names = config["textures"];
    std::vector<sf::Texture*> textures = getTextures(texture_names);
    std::vector<std::vector<int>> grid = config["grid"]["1"];

    playingfield = new PlayingField{0, 0, textures, grid};

    enemy_path = playingfield->getEnemyPath();
}

void GameState::initBase()
{
    nlohmann::json config;
    config = (datahandler->getConfig())["game_entity"]["base"];
    std::vector<std::string> texture_names = config["textures"];
    std::vector<sf::Texture*> textures = getTextures(texture_names);

    std::vector<int> road_end_index = playingfield->getRoadEndIndex();
    sf::Vector2f base_coordinate = playingfield->getSquareMiddle(road_end_index[0]*35, road_end_index[1]*35);

    base = new Base{base_coordinate.x, base_coordinate.y, textures, config["parameters"]};

    datahandler->setBasePtr(base);
}

void GameState::initPlayerfigure()
{
    nlohmann::json config;
    config = (datahandler->getConfig())["game_entity"]["playerfigure"];
    std::vector<std::string> texture_names = config["textures"];
    std::vector<sf::Texture*> textures = getTextures(texture_names);

    playerfigure = new PlayerFigure(350, 350, textures, config["parameters"]);
}

void GameState::initButtons()
{
    sf::Texture * transparent_texture = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    leveldisplay = new Button(800,350,100,40,transparent_texture,"level",font);
    moneydisplay = new Button(800,370,100,40,transparent_texture,"money",font);
    hpdisplay = new Button(800,390,100,40,transparent_texture,"hp",font);
}

void GameState::initSprites()
{
    sf::Texture * fighterjet_texture = texture_map->at("FighterJet_ani1");
    auto size{fighterjet_texture->getSize()};
    fighterjet_sprite.setOrigin(size.x/2, size.y/2);
    fighterjet_sprite.setTexture(*fighterjet_texture);
    fighterjet_sprite.setRotation(270);

    sf::Texture * handsanitizer_texture = texture_map->at("HandSanitizerShoot_ani1");
    size = handsanitizer_texture->getSize();
    handsanitizer_sprite.setOrigin(size.x/2, size.y/2);
    handsanitizer_sprite.setTexture(*handsanitizer_texture);
}


void GameState::getLevelParameters()
{
    nlohmann::json config_file;
    config_file = (datahandler->getConfig())["level"];
    std::string level_str{std::to_string(level)};

    int enemeis_to_spawn = config_file[level_str]["amount"];
    int enemeis_spawn_interval = config_file[level_str]["time_interval"];

    enemy_amount = enemeis_to_spawn;
    enemy_spawn_time = enemeis_spawn_interval;
    moneybag_spawn_time = config_file[level_str]["moneybag_time_interval"];

    datahandler->setCurrentLevel(level);
}

void GameState::updateObjects()
{
    if (internal_state == 1)
    {
        for (std::vector<Enemy *>::iterator it = enemies.begin();
                                        it != enemies.end();)
        {
            int enemy_index{it - enemies.begin()};
            checkEnemyCollisions(enemies.at(enemy_index));

            if ((*it)->isDestroyed())
            {
                delete (*it);
                it = enemies.erase(it);
            }
            else
            {
                (*it)->updateObject();
                ++it;
            }
        }

        for (std::vector<Projectile *>::iterator it = projectiles.begin();
                                        it != projectiles.end();)
        {
            if ((*it)->isDestroyed())
            {
                delete (*it);
                it = projectiles.erase(it);
            }
            else
            {
                (*it)->updateObject();
                ++it;
            }
        }

        for (std::vector<DynamicTower *>::iterator it = dynamic_towers.begin();
                                        it != dynamic_towers.end();
                                        ++it)
        {
            (*it)->updateObject();
        }

        for (std::vector<StaticTower *>::iterator it = static_towers.begin();
                                        it != static_towers.end();
                                        ++it)
        {
            (*it)->updateObject();
        }

        checkPlayerFigureCollisions(playerfigure);

        for (std::vector<MoneyBag *>::iterator it = moneybags.begin();
                                        it != moneybags.end();)
        {
            if ((*it)->isDestroyed())
            {
                delete (*it);
                it = moneybags.erase(it);
            }
            else
            {
                (*it)->updateObject();
                ++it;
            }
        }

        base->updateObject();
    }

    playingfield->updateObject();
    playerfigure->updateObject();
    updateButtons();
}

void GameState::updateButtons()
{
    std::string level_str = "Level : " + std::to_string(level);
    leveldisplay->changeText(level_str);

    std::string money_str = "Money : " + std::to_string(base->getMoney());
    moneydisplay->changeText(money_str);

    std::string hp_string = "HP : " + std::to_string(base->getLife());
    hpdisplay->changeText(hp_string);
}

void GameState::checkEnemyCollisions(Enemy * enemy)
{

    for (std::vector<Projectile *>::iterator it = projectiles.begin();
                                    it != projectiles.end();
                                    ++it)
    {
        int projectile_index{it - projectiles.begin()};
        enemy->checkCollision(projectiles.at(projectile_index));
    }

    for (std::vector<StaticTower *>::iterator it = static_towers.begin();
                                    it != static_towers.end();
                                    ++it)
    {
        int tower_index{it - static_towers.begin()};
        enemy->checkCollision(static_towers.at(tower_index));
    }

    enemy->checkCollision(base);
}

void GameState::checkPlayerFigureCollisions(PlayerFigure * playerfigure)
{
    for (std::vector<MoneyBag *>::iterator it = moneybags.begin();
                                    it != moneybags.end();
                                    ++it)
    {
        int bag_index{it - moneybags.begin()};
        playerfigure->checkCollision(moneybags.at(bag_index));
    }
}


void GameState::handlePrepState()
{
    current_menu = prep_menu;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        next_state_id = 2;
    }

    sf::Event event;
    while (window->pollEvent(event))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            auto mouse {event.mouseButton};
            if (mouse.button == sf::Mouse::Button::Left)
            {
                buy_option_select = current_menu->getSelectedOption(mouse.x, mouse.y);

                if (buy_option_select == 0)
                {
                    // Do nothing
                }
                else if (buy_option_select == 1)
                {
                    internal_state = 1; // Run state
                    current_menu = run_menu;
                }
                else
                {
                    internal_state = 2; // buy state
                }
            }
        }
        
        else
        {
            next_state_id = 1;
        }
    }
    playerfigure->controlPlayer();
}

void GameState::handleRunState()
{
    playerfigure->controlPlayer();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        next_state_id = 2;
    }
    else
    {
        next_state_id = 1;
    }

    if (base->getLife() <= 0)
    {
        /* If base hp is 0 or less, the game ends (game over)*/
        datahandler->saveNewHighscore(score);
        next_state_id = 8;
    }
    else if (enemy_amount > 0)
    {
        enemySpawner();
    }
    else if (enemies.empty())
    {
        ++level;
        datahandler->setCurrentLevel(level);


        for (std::vector<Projectile *>::iterator it = projectiles.begin();
                                        it != projectiles.end();)
        {
          delete (*it);
          it = projectiles.erase(it);
        }

        for (std::vector<MoneyBag *>::iterator it = moneybags.begin();
                                        it != moneybags.end();)
        {
          delete (*it);
          it = moneybags.erase(it);
        }

        score += getLevelScore();

        nlohmann::json config_file;
        config_file = datahandler->getConfig();
        int max_level(config_file["max_level"]);

        if (level > max_level)
        {
            datahandler->saveNewHighscore(score);

            next_state_id = 5;
        }
        else
        {
            /* Loads in parameters for the next level */
            getLevelParameters();
        }


        int money_from_round = config_file["end_of_round_money"];

        base->addMoney(money_from_round);

        internal_state = 0;
    }

    moneybagSpawner();
}

void GameState::handleBuyState()
{
    switch (buy_option_select)
    {
    case 2: //fighterjet
        buyFighterjet();
        break;

    case 3: // HandsanitizerTower
        buyHandsanitizer();
        break;
    }
}


std::vector<sf::Texture*> GameState::getTextures(std::vector<std::string> texture_names)
{
    std::vector<sf::Texture*> textures{};

    for (std::vector<std::string>::iterator it = texture_names.begin();
                                    it != texture_names.end();
                                    ++it)
    {
        textures.push_back(texture_map->at(*it));
    }

    return textures;
}

void GameState::buyFighterjet()
{
    nlohmann::json config = (datahandler->getConfig());
    nlohmann::json parameters = config["game_entity"]
                                      ["dynamictower"]
                                      ["fighterjet"]
                                      ["parameters"];
    nlohmann::json proj_parameters = config["game_entity"]
                                           ["projectile"]
                                           ["spit"]
                                           ["parameters"];
    int cost = parameters["cost"];
    std::vector<std::string> texture_names = config["game_entity"]
                                                   ["dynamictower"]
                                                   ["fighterjet"]
                                                   ["textures"];

    if (base->getMoney() >= cost)
    {
        currently_placing_tower = 1;

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {

                auto mouse{event.mouseButton};
                if (mouse.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f corrected_mouse = getClosestPlayfieldPosition(mouse.x, mouse.y);
                    bool occupied = playingfield->
                                    isOccupied(corrected_mouse.x, corrected_mouse.y);
                    if (!occupied)
                    {
                        base->spendMoney(cost);
                        std::vector<sf::Texture*> textures = getTextures(texture_names);
                        DynamicTower * new_fighterjet
                        {
                            new FighterjetTower(corrected_mouse.x,
                                                corrected_mouse.y,
                                                textures,
                                                parameters,
                                                &projectiles,
                                                proj_parameters)
                        };
                        dynamic_towers.push_back(new_fighterjet);
                        currently_placing_tower = 0;
                        internal_state = 0;
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    currently_placing_tower = 0;
                    internal_state = 0;
                }
            }
        }
    }
    else
    {
        internal_state = 0;
    }
}

void GameState::buyHandsanitizer()
{
    nlohmann::json config = (datahandler->getConfig());
    nlohmann::json parameters = config["game_entity"]
                                      ["statictower"]
                                      ["handsanitizer"]
                                      ["parameters"];
    nlohmann::json proj_parameters = config["game_entity"]
                                           ["projectile"]
                                           ["spit"]
                                           ["parameters"];
    int cost = parameters["cost"];
    std::vector<std::string> texture_names = config["game_entity"]
                                                   ["statictower"]
                                                   ["handsanitizer"]
                                                   ["textures"];

    if (base->getMoney() >= cost)
    {
        currently_placing_tower = 2;

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {

                auto mouse{event.mouseButton};
                if (mouse.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f corrected_mouse = getClosestPlayfieldPosition(mouse.x, mouse.y);
                    bool occupied = playingfield->
                                    isOccupied(corrected_mouse.x, corrected_mouse.y);
                    if (!occupied)
                    {
                        base->spendMoney(cost);
                        std::vector<sf::Texture*> textures = getTextures(texture_names);
                        sf::Vector2f square_middle = playingfield->
                                                     getSquareMiddle(corrected_mouse.x, corrected_mouse.y);
                        StaticTower * new_handsanitizer
                        {
                            new HandSanitizerTower(square_middle.x,
                                                    square_middle.y,
                                                    textures,
                                                    parameters,
                                                    &projectiles,
                                                    proj_parameters)
                        };
                        static_towers.push_back(new_handsanitizer);
                        currently_placing_tower = 0;
                        internal_state = 0;
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    currently_placing_tower = 0;
                    internal_state = 0;
                }
            }
        }
    }
    else
    {
        internal_state = 0;
    }
}

void::GameState::enemySpawner()
{
    auto curr_time{clock.getElapsedTime()};
    auto time_diff{curr_time - last_spawn_time};

    if (time_diff.asSeconds() >= enemy_spawn_time)
    {
        nlohmann::json config;
        config = (datahandler->getConfig())["game_entity"]
                                           ["enemy"]
                                           ["covid"];

        std::vector<std::string> texture_names = config["textures"];

        nlohmann::json parameters;
        parameters = config["parameters"];

        std::string lvl{std::to_string(level)};
        nlohmann::json lvl_parameter;
        lvl_parameter = parameters[lvl];

        std::vector<int> start_index = playingfield->getRoadStartIndex();
        sf::Vector2f start_pos = playingfield->getSquareMiddle(
                                                35*start_index[1],
                                                35*start_index[0]);

        std::vector<sf::Texture*> textures = getTextures(texture_names);

        Enemy * new_enemy
        {
            new Enemy(start_pos.x,
                      start_pos.y,
                      textures,
                      lvl_parameter,
                      &enemy_path)
        };

        enemies.push_back(new_enemy);

        last_spawn_time = clock.getElapsedTime();

        enemy_amount--;
    }
}

void GameState::moneybagSpawner()
{
    auto curr_time{clock.getElapsedTime()};
    auto time_diff{curr_time - moneybag_last_spawn_time};

    if (time_diff.asSeconds() >= moneybag_spawn_time)
    {
        nlohmann::json config;
        config = (datahandler->getConfig())["game_entity"]
                                           ["moneybag"];

        std::vector<std::string> texture_names = config["textures"];

        nlohmann::json parameters;
        parameters = config["parameters"];

        int randx;
        srand(time(NULL));
        randx = rand() % 700 + 1;

        std::vector<int> start_index = playingfield->getRoadStartIndex();
        sf::Vector2f start_pos = playingfield->getSquareMiddle(start_index[1], start_index[0]);
        std::vector<sf::Texture*> textures = getTextures(texture_names);
        MoneyBag * new_moneybag
        {
            new MoneyBag(randx,
                      0, 1,
                      textures,
                      parameters,
                      base)
        };

        moneybags.push_back(new_moneybag);
        moneybag_last_spawn_time = clock.getElapsedTime();
    }
}

sf::Vector2f GameState::getClosestPlayfieldPosition(int x, int y)
{
    if (x >= 700)
    {
        x = 699;
    }
    else if (x <= 0)
    {
        x = 1;
    }

    if (y >= 700)
    {
        y = 699;
    }
    else if (y <= 0)
    {
        y = 1;
    }

    sf::Vector2f closest_position{x,y};

    return closest_position;
}

int GameState::getLevelScore()
{
    /* Calculates the score for the current level */
    int score{level * (base->getLife() + base->getMoney())};

    return score;
}
