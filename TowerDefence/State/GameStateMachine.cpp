#include "GameStateMachine.hpp"

GameStateMachine::GameStateMachine(std::string t_folder_path,
                                   std::string f_folder_path,
                                   DataHandler * datahandler_)
                 : saved_game_state{nullptr}, datahandler{datahandler_}
{
    loadTextures(t_folder_path);
    loadFonts(f_folder_path);
    current_state = createState(0);
    window.setFramerateLimit(datahandler->getConfig()["fps_limit"]);
}

GameStateMachine::~GameStateMachine()
{
    delete current_state;
    delete saved_game_state;

    for (std::map<std::string, sf::Texture *>::iterator
                                    it = texture_map.begin();
                                    it != texture_map.end();
                                    ++it)
    {
        delete it->second;
    }

    for (std::map<std::string, sf::Font *>::iterator
                                    it = font_map.begin();
                                    it != font_map.end();
                                    ++it)
    {
        delete it->second;
    }

}

void GameStateMachine::runState()
{
    int next_state_id{};
    State * next_state_ptr{};

    while (next_state_id != -1 && window.isOpen())
    {

        if (next_state_id != current_state->getStateID())
        {
            /* Sets saved GameState to current if there
                is a saved state (and next ID is 1).
                Else, create a new state */
            if (next_state_id == 1 && saved_game_state != nullptr)
            {
                next_state_ptr = saved_game_state;
            }
            else
            {
                next_state_ptr = createState(next_state_id);
            }

            updateCurrentState(next_state_ptr);
        }

        updateState();
        next_state_id = getNextStateID();
        renderState();
        window.display();
    }
}

int GameStateMachine::getNextStateID()
{
    return current_state->getNextStateID();
}

State * GameStateMachine::createState(int state_id)
{
    State * new_state{};
    DataHandler * datahandler_ptr{datahandler};
    sf::RenderWindow * window_ptr{&window};
    std::map<std::string, sf::Texture*> * texture_map_ptr{&texture_map};
    std::map<std::string, sf::Font*> * font_map_ptr{&font_map};

    switch (state_id)
    {
    case 0:
        new_state = new MainMenuState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;

    case 1:
        new_state = new GameState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;

    case 2:
        new_state = new PauseState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;


    case 5:
        new_state = new GameFinishedState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;

    case 7:
        new_state = new HighscoreState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;

    case 8:
        new_state = new GameOverState(window_ptr,datahandler_ptr,texture_map_ptr,font_map_ptr);
        break;
    }

    return new_state;
}

void GameStateMachine::updateState()
{
    current_state->updateState();
}

void GameStateMachine::renderState()
{
    window.clear();
    current_state->render();
}

void GameStateMachine::loadTextures(std::string const & folder_path)
{
    auto texture_dir_json = datahandler->getConfig()["texture"];
    std::map<std::string, std::string> texture_dir_map = texture_dir_json;

    for (auto const& x : texture_dir_map)
    {
        std::string texture_name = x.first;
        std::string texture_file_name = x.second;
        addTexture(folder_path , texture_name, texture_file_name);
    }
}

void GameStateMachine::loadFonts(std::string const & folder_path)
{
    auto font_dir_json = datahandler->getConfig()["font"];
    std::map<std::string, std::string> font_dir_map = font_dir_json;

    for (auto const& x : font_dir_map)
    {
        std::string font_name = x.first;
        std::string font_file_name = x.second;
        addFont(folder_path , font_name, font_file_name);
    }
}

void GameStateMachine::addTexture(std::string const & folder_path,
                                  std::string const & texture_name,
                                  std::string const & filename)
{
    sf::Texture* texture{new sf::Texture()};
    texture->loadFromFile(folder_path + "/" + filename);
    texture_map[texture_name] = texture;
}

void GameStateMachine::addFont(std::string const & folder_path,
                               std::string const & font_name,
                               std::string const & filename)
{
    sf::Font* font{new sf::Font()};
    font->loadFromFile(folder_path + "/" + filename);
    font_map[font_name] = font;
}

void GameStateMachine::updateCurrentState(State * next_state_ptr)
{
    /* Saves the current state if current state is GameState (ID: 1) */
    if (current_state->getStateID() == 1)
    {
        saved_game_state = current_state;
    }
    else
    {
        delete current_state;
    }

    /* Delete saved GameState if next state is MainMenuState (ID: 0) */
    if (next_state_ptr->getStateID() == 0)
    {
        delete saved_game_state;

        saved_game_state = nullptr;
    }

    current_state = next_state_ptr;
}


// Functions for testing

State * GameStateMachine::getCurrentState()
{
    return current_state;
}

State * GameStateMachine::getSavedState()
{
    return saved_game_state;
}
