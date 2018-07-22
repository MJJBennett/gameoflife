#include "game.h"

int main(int argc, char * argv[]) {
    auto write = debug::get_debugger("main.cpp");
    std::string config_file;
    if (argc <= 1) config_file = "conway.conf";
    else config_file = argv[1];
    write(config_file);

    //Create and run the game
    game g;
    g.init();
    g.run();
    return 0;
}
