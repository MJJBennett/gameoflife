#include "game.h"

void game::init() {
    write = debug::get_debugger("game.cpp");
    is_init = true;
}

void game::run() {
    if (!is_init) init();

    //Create resource manager
    auto r = std::make_unique<ResourceManager>();
    r->preload_resource("images/red.png");
    r->preload_resource("RECT_GAMECPP"); //I really don't like this, would definitely do it differently

    //Create a window
    write("Creating window.");
    w.create(sf::VideoMode(800, 600), "Example Window");
    write("Window creation complete.");

    World world;
    world.init(r.get());

/*
    int draw_rects = 0;
    auto rect_p = r->retrieve_resource("images/red.png");
    if (rect_p == nullptr) write("Recieved a null resource!");
    sf::Sprite rect;
    rect.setTexture(std::get<sf::Texture>(*rect_p));
*/

    //Main loop
    write("Entering main loop.");
    while (w.isOpen()) {

        //Basic event loop
        sf::Event e{};
        while (w.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::KeyPressed:
                                         switch(e.key.code) {
                                             case sf::Keyboard::Escape:
                                                 w.close();
                                                 continue;
                                             case sf::Keyboard::Key::P:
                                                 world.set_square_size(world.get_square_size() + 1);
                                                 continue;
                                             case sf::Keyboard::Key::D:
                                                 //Debug option
                                                 write("Printing debug information into stdout.");
                                                 continue;
                                             default:
                                                 continue;
                                         }
                case sf::Event::Resized: w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                                         continue;
                case sf::Event::Closed:  w.close();
                                         continue;
                default:
                    continue;
            }
        }

        //Do logical updates here


        //Clears the window for drawing
        w.clear(sf::Color::Black);

        //For each boolean value, draw or not based off of its toggle
        our_rect.setFillColor(sf::Color::Red);
        for (int x = 0; x < world_width; x++) {
            for (int y = 0; y < world_height; y++) {
                if (world_state[coord(x, y)]) draw_rect(x, y);
            }
        }

        w.display();
        //while(true);
    }
    //Ensure the window is closed
    w.close();
}
