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
    w.create(sf::VideoMode(500, 500), "Example Window");
    write("Window creation complete.");

    world.init(r.get());

/*
    int draw_rects = 0;
    auto rect_p = r->retrieve_resource("images/red.png");
    if (rect_p == nullptr) write("Recieved a null resource!");
    sf::Sprite rect;
    rect.setTexture(std::get<sf::Texture>(*rect_p));
*/

    //Main loop
    int _tick = 0;
    write("Entering main loop.");
    long long do_update = 0;
    sf::Text key_state;
    key_state.setPosition(5, 5);
    sf::Font font;
    key_state.setFont(font);

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
                                             case sf::Keyboard::Key::Return:
                                             case sf::Keyboard::Key::A:
                                                 if (key_combo.active) {
                                                     do_update += key_combo.get_num();
                                                     key_combo.reset();
                                                 }
                                                 else do_update++;
                                                 write("Updates left to handle: " + std::to_string(do_update));
                                                 if (do_update < 0) debug::err(write, "Less than 0 updates found!");
                                                 continue;
                                             case sf::Keyboard::Key::D:
                                                 //Debug option
                                                 write("Printing debug information into stdout.");
                                                 write("\tUpdates left to handle: " + std::to_string(do_update));
                                                 write("\tNumber of ticks since start: " + std::to_string(_tick));
                                                 world.dump_debug();
                                                 continue;
                                             case sf::Keyboard::Key::R:
                                                 write("Resetting world.");
                                                 world.reset();
                                                 key_combo.reset();
                                                 do_update = 0;
                                                 continue;
                                             default:
                                                 handle_keyboard(e.key.code);
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
        if (do_update > 0) {
            world.update();
            do_update--;
        }

        //Clears the window for drawing
        w.clear(sf::Color::Blue);

        for (auto && sqr : world) {
            w.draw(sqr);
        }

        if (key_combo.active) {
            key_state.setString(key_combo.str_state);
//            write(key_combo.str_state);
            w.draw(key_state);
        }

        w.display();
        _tick++;
        //if (!(_tick % 60)) std::cout << _tick << '\n';
    }
    //Ensure the window is closed
    w.close();
}

void game::handle_keyboard(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Key::Num0:
        case sf::Keyboard::Key::Numpad0:
            if (key_combo.active)
                key_combo.add_num(0);
            break;
        case sf::Keyboard::Key::Num1:
        case sf::Keyboard::Key::Numpad1:
            key_combo.add_num(1);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num2:
        case sf::Keyboard::Key::Numpad2:
            key_combo.add_num(2);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num3:
        case sf::Keyboard::Key::Numpad3:
            key_combo.add_num(3);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num4:
        case sf::Keyboard::Key::Numpad4:
            key_combo.add_num(4);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num5:
        case sf::Keyboard::Key::Numpad5:
            key_combo.add_num(5);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num6:
        case sf::Keyboard::Key::Numpad6:
            key_combo.add_num(6);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num7:
        case sf::Keyboard::Key::Numpad7:
            key_combo.add_num(7);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num8:
        case sf::Keyboard::Key::Numpad8:
            key_combo.add_num(8);
            key_combo.active = true;
            break;
        case sf::Keyboard::Key::Num9:
        case sf::Keyboard::Key::Numpad9:
            key_combo.add_num(9);
            key_combo.active = true;
            break;
        default:
            break;
    }
}