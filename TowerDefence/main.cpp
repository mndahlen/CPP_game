#include "State/GameStateMachine.hpp"

int main()
{
    /* Paths to the config and textures folders */
    std::string path_from_build{"TowerDefence/"};
    std::string mediafolder_path{path_from_build + "media_files/"};
    std::string png_folder{mediafolder_path + "png_images"};
    std::string font_folder{mediafolder_path + "fonts"};
    std::string config_path{path_from_build + "config/config.json"};

    /* Datahandler */
    DataHandler datahandler(config_path);

    GameStateMachine tower_defence{png_folder, font_folder, &datahandler};

    tower_defence.runState();

    return 0;
}