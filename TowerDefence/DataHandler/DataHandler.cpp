#include "DataHandler.hpp"

DataHandler::DataHandler(std::string config_path_) : config_path{config_path_}
{
    game_config = loadGameConfig();
}

nlohmann::json DataHandler::getConfig()
{
    return game_config;
}

nlohmann::json DataHandler::loadGameConfig()
{
    nlohmann::json json_config;
    std::ifstream config_file(config_path, std::ifstream::binary);
    config_file >> json_config;

    return json_config;
}

void DataHandler::saveHighScore(std::vector<int> highscore_vector)
{    
    game_config["highscore"] = highscore_vector;
    std::ofstream myfile;

    myfile.open(config_path);
    myfile << game_config;
    myfile.close();
}

std::vector<int> DataHandler::getHighscore()
{
    return game_config["highscore"];
}

void DataHandler::saveNewHighscore(int score)
{
    std::vector<int> highscore = getHighscore();

    highscore.push_back(score);
    std::sort(highscore.begin(), highscore.end(),std::greater<int>());

    if (highscore.size() > 5)
    {
        highscore.pop_back();
    }

    saveHighScore(highscore);
}

void DataHandler::reload()
{
    game_config = loadGameConfig();
}

Base * DataHandler::getBasePtr()
{
    return base_ptr;
}

void DataHandler::setBasePtr(Base * base_ptr_)
{
    base_ptr = base_ptr_;
}

int DataHandler::getCurrentLevel()
{
    return current_level;
}

void DataHandler::setCurrentLevel(int current_level_)
{
    current_level = current_level_;
}



