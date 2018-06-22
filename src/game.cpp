#include "game.h"

void game::init() {
    write = debug::get_debugger("game.cpp");
    is_init = true;
}

void game::run() {
    if (!is_init) init();

    //Create a window
    write("Creating window.");
    sf::RenderWindow w(sf::VideoMode(800, 600), "Example Window");
    write("Window creation complete.");

    //Main loop
    while (w.isOpen()) {

        //Basic event loop
        sf::Event e;
        while (w.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Resized: w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                                         continue;
                case sf::Event::Closed:  w.close();
                                         continue;
            }
        }

        //Do logical updates here

        w.clear(sf::Color(0,0,0));
        
        //Draw here with w.draw(//drawable)
        
        w.display();

    }
    //Ensure the window is closed
    w.close();
}
