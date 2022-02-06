//"https://ideone.com/KXNIx1"
//"https://github.com/nlohmann/json/tree/release/3.9.1"
//https://stackoverflow.com/questions/35820879/read-a-dat-file-in-c
//https://stackoverflow.com/questions/43230542/write-vectorvectorfloat-to-binary-file/43230648
//https://www.boost.org/doc/libs/1_73_0/libs/serialization/doc/tutorial.html

//https://stackoverflow.com/questions/19723170/c-writing-object-to-binary-file
//https://courses.cs.vt.edu/~cs2604/fall00/binio.html

#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "../GameObject/StaticObject/Base/Base.hpp"

//Third party
#include "../../third_party/nlohmann/json.hpp"

class DataHandler
{
    public:
        DataHandler(std::string config_path_);
        ~DataHandler() = default;
        nlohmann::json getConfig();
        std::vector<int> getHighscore();
        Base * getBasePtr();
        void setBasePtr(Base * base_ptr_);
        void setCurrentLevel(int level);
        int getCurrentLevel();
        void saveNewHighscore(int score);
        void reload();

    private:
        nlohmann::json game_config{};
        std::string config_path{};
        void saveHighScore(std::vector<int>);
        Base * base_ptr{nullptr};
        int current_level;

        nlohmann::json loadGameConfig();
};

#endif