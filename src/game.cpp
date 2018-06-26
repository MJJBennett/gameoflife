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

    //Create a window
    write("Creating window.");
    sf::RenderWindow w(sf::VideoMode(800, 600), "Example Window");
    write("Window creation complete.");

    int debug_counter = 0;

    int draw_rects = 0;
    debug::write_break(++debug_counter);
    auto rect_p = r->retrieve_resource("images/red.png");
    if (rect_p == nullptr) write("Recieved a null resource!");
    debug::write_break(++debug_counter);
    sf::Sprite rect;
    debug::write_break(++debug_counter);
    rect.setTexture(std::get<sf::Texture>(*rect_p));
    debug::write_break(++debug_counter);

    //Main loop
    while (w.isOpen()) {

        //Basic event loop
        sf::Event e;
        while (w.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::KeyPressed:
                                         switch(e.key.code) {
                                             case sf::Keyboard::Escape:
                                                w.close();
                                                continue;
                                             case sf::Keyboard::Key::A:
                                                draw_rects++;
                                                continue;
                                         }
                case sf::Event::Resized: w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                                         continue;
                case sf::Event::Closed:  w.close();
                                         continue;
            }
        }

        //Do logical updates here

        w.clear(sf::Color::White);
        
        //Draw here with w.draw(//drawable)
        for (int i = 0; i < draw_rects; i++) {
            rect.setPosition(i * 30, i * 30);
            w.draw(rect);
        }
        
        w.display();

    }
    //Ensure the window is closed
    w.close();
}
