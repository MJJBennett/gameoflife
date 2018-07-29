#include "game.h"
#include "ConfigFile.h"

int main(int argc, char * argv[]) {
    //Load application configuration
    std::string config_file = "../conway.config";
    if(argc >= 2) config_file = argv[1];
    ConfigFile config(config_file);

    //Create and run the game
    game g(std::move(config));
    g.init();
    g.run();
    return 0;
}
