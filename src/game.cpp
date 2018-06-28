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

/*
    int draw_rects = 0;
    auto rect_p = r->retrieve_resource("images/red.png");
    if (rect_p == nullptr) write("Recieved a null resource!");
    sf::Sprite rect;
    rect.setTexture(std::get<sf::Texture>(*rect_p));
*/

    auto rect_p = r->retrieve_resource("RECT_GAMECPP");
    if (!rect_p) write("Rect could not be created!"); 
    our_rect = std::get<sf::RectangleShape>(*(r->retrieve_resource("RECT_GAMECPP")));
    our_rect.setFillColor(sf::Color::Red);
    set_square_size(5);

    for (int x = 0; x < 11; x++) {
        
        std::vector<bool> b(10);
        if (x%2) std::fill(b.begin(), b.end(), true);
        state.push_back(b);
    }

    //Main loop
    write("Entering main loop.");
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
                                             case sf::Keyboard::Key::P:
                                                set_square_size(square_size + 1);
                                                continue;
                                         }
                case sf::Event::Resized: w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                                         continue;
                case sf::Event::Closed:  w.close();
                                         continue;
            }
        }

        //Do logical updates here

        w.clear(sf::Color::Black);

        for (int x = 0; x < state.size(); x++) {
            for (int y = 0; y < state.at(x).size(); y++) if (state.at(x).at(y)) draw_rect(x, y);
        }
        //For each boolean value, draw or not based off of its toggle

        w.display();

    }
    //Ensure the window is closed
    w.close();
}

void game::set_square_size(int s) {
    square_size = s;
    our_rect.setSize({s, s});
}

void game::draw_rect(int x, int y) {
    our_rect.setPosition(x*square_size, y*square_size);
    w.draw(our_rect);
}