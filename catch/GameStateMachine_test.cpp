#include "catch_files/catch.hpp"
#include <iostream>
#include "../TowerDefence/State/GameStateMachine.hpp"
#include "../TowerDefence/State/GameFinishedState.hpp"
#include "../TowerDefence/State/GameState.hpp"
#include "../TowerDefence/State/MainMenuState.hpp"
#include "../TowerDefence/State/PauseState.hpp"

TEST_CASE("GameStateMachine should create correct state based on ID")
{
    std::string mediafolder_path{"../TowerDefence/media_files/"};
    std::string png_folder{mediafolder_path + "png_images"};
    std::string font_foler{mediafolder_path + "fonts"};
    std::string config_path{"../TowerDefence/config/config.json"};
    DataHandler dh(config_path);
    GameStateMachine s_m{png_folder, font_foler, &dh};

    State * casted_ptr{nullptr};
    State * state_ptr{s_m.createState(0)};
    CHECK(dynamic_cast<MainMenuState*>(state_ptr));
    delete state_ptr;

    state_ptr = s_m.createState(1);
    CHECK(dynamic_cast<GameState*>(state_ptr));
    delete state_ptr;

    state_ptr = s_m.createState(2);
    CHECK(dynamic_cast<PauseState*>(state_ptr));
    delete state_ptr;

    state_ptr = s_m.createState(5);
    CHECK(dynamic_cast<GameFinishedState*>(state_ptr));
    delete state_ptr;

}

TEST_CASE("GameStateMachine should have MainMenuState as inital state and have nothing saved")
{
    std::string mediafolder_path{"../TowerDefence/media_files/"};
    std::string png_folder{mediafolder_path + "png_images"};
    std::string font_foler{mediafolder_path + "fonts"};
    std::string config_path{"../TowerDefence/config/config.json"};
    DataHandler dh(config_path);
    GameStateMachine s_m{png_folder, font_foler, &dh};
    
    CHECK(dynamic_cast<MainMenuState*>(s_m.getCurrentState()));
    CHECK_FALSE(s_m.getSavedState());
}

TEST_CASE("GameStateMachine should change current state if there is a statechange")
{
    std::string mediafolder_path{"../TowerDefence/media_files/"};
    std::string png_folder{mediafolder_path + "png_images"};
    std::string font_foler{mediafolder_path + "fonts"};
    std::string config_path{"../TowerDefence/config/config.json"};
    DataHandler dh(config_path);
    GameStateMachine s_m{png_folder, font_foler, &dh};

    CHECK(dynamic_cast<MainMenuState*>(s_m.getCurrentState()));

    State * new_state{s_m.createState(1)};

    s_m.updateCurrentState(new_state);

    CHECK_FALSE(dynamic_cast<MainMenuState*>(s_m.getCurrentState()));
    CHECK(dynamic_cast<GameState*>(s_m.getCurrentState()));
}

TEST_CASE("GameStateMachine should save a GameState if state is changed")
{
    std::string mediafolder_path{"../TowerDefence/media_files/"};
    std::string png_folder{mediafolder_path + "png_images"};
    std::string font_foler{mediafolder_path + "fonts"};
    std::string config_path{"../TowerDefence/config/config.json"};
    DataHandler dh(config_path);
    GameStateMachine s_m{png_folder, font_foler, &dh};

    CHECK_FALSE(s_m.getSavedState());

    State * game_state{s_m.createState(1)};

    s_m.updateCurrentState(game_state);

    State * new_state{s_m.createState(2)}; // ID 2 = PauseState

    s_m.updateCurrentState(new_state);

    CHECK(s_m.getSavedState() == game_state);
    CHECK(s_m.getCurrentState() == new_state);
}