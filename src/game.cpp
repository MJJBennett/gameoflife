#include <chrono>
#include "game.h"

void game::init() {
    write = debug::get_debugger("game.cpp");
    is_init = true;
}

void game::run() {
    if (!is_init) init();

    //Create resource manager
    auto r = std::make_unique<ResourceManager>();
    r->preload_resource("RECT_WORLD_CPP"); //I really don't like this, would definitely do it differently

    //Create a window
    write("Creating window.");
    w.create(sf::VideoMode(static_cast<unsigned int>(std::stoi(config.get_or_add_default("width", "500"))),
                           static_cast<unsigned int>(std::stoi(config.get_or_add_default("height", "500")))),
                           config.get_or_add_default("game title", "Game of Life"));
    write("Window creation complete.");

    world.init(r.get(), (unsigned int)std::stoi(config.get_or_add_default("canvas width", "100")), (unsigned int)std::stoi(config.get_or_add_default("canvas height", "100")));

    //Ideally this would all be done through the resource manager.
    //This is on the todo list.
    sf::Text key_state;
    sf::Font font;
    font.loadFromFile("../resources/fonts/RobotoMono/Regular.ttf");
    key_state.setCharacterSize(14);
    key_state.setFont(font);
    key_state.setPosition(5, w.getSize().y - 24);

    sf::Text update_state;
    update_state.setCharacterSize(14);
    update_state.setFont(font);
    update_state.setPosition(w.getSize().x - (update_state.getLocalBounds().width + 5), w.getSize().y - 24);

    sf::Text fps_state;
    fps_state.setCharacterSize(14);
    fps_state.setFont(font);
    fps_state.setPosition(w.getSize().x - fps_state.getLocalBounds().width - 5, 5);

    //Get some configuration information (to avoid having to cast strings to ints more than once)
    bool show_numbers = (config.get_or_add_default("show numbers", "true") == "true");
    bool show_fps = (config.get_or_add_default("show fps", "false") == "true");

    unsigned int text_update_rate = (unsigned int)std::stoi(config.get_or_add_default("text update rate", "1"));
    unsigned int fps_update_rate = (unsigned int)std::stoi(config.get_or_add_default("fps update rate", "10"));
    unsigned int fps_limit = (unsigned int)std::stoi(config.get_or_add_default("framerate limit", "0"));
    if (fps_limit >= 0) w.setFramerateLimit(fps_limit);

    auto now = std::chrono::system_clock::now();
    auto previous_frame = now;
    using second = std::chrono::duration<float>;

    //Main loop
    write("Entering main loop.");
    int _tick = 0;
    long long do_update = 0;
    int fps = 0;
    while (w.isOpen()) {
        //Basic event loop
        sf::Event e{};
        while (w.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::KeyPressed:
                     switch(e.key.code) {
                         case sf::Keyboard::Key::Left:
                         case sf::Keyboard::Escape:
                             w.close();
                             continue;
                         case sf::Keyboard::Key::P:
                             world.set_square_size(world.get_square_size() + 1);
                             continue;
                         case sf::Keyboard::Key::Right:
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
                         case sf::Keyboard::Key::Up:
                         case sf::Keyboard::Key::D:
                             //Debug option
                             write("Printing debug information into stdout.");
                             write("\tUpdates left to handle: " + std::to_string(do_update));
                             write("\tNumber of ticks since start: " + std::to_string(_tick));
                             now = std::chrono::system_clock::now();
                             fps = (int) (1 / ((std::chrono::duration_cast<second>(now - previous_frame)).count() / fps_update_rate));
                             write("\tCurrent FPS: " + std::to_string(1 / ((std::chrono::duration_cast<second>(now - previous_frame)).count() / (_tick % fps_update_rate + 1))));
                             //world.dump_debug();
                             continue;
                         case sf::Keyboard::Key::Down:
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
                case sf::Event::MouseButtonReleased:
                    if (e.mouseButton.x > 0 && e.mouseButton.x < w.getSize().x
                        && e.mouseButton.y > 0 && e.mouseButton.y < w.getSize().y) {
                        //If the mouse button was released while in the window
                        world.invert(e.mouseButton.x, e.mouseButton.y);
                    }
                    continue;
                case sf::Event::Resized:
                    w.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
                    continue;
                case sf::Event::Closed:
                    w.close();
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
            if (sqr.getPosition().x < w.getSize().x && sqr.getPosition().y < w.getSize().y)
                w.draw(sqr);
        }

        if (key_combo.active) {
            if (_tick % text_update_rate == 0) {
                key_state.setString(key_combo.str_state);
                key_state.setPosition(5, w.getSize().y - 24);
            }
            w.draw(key_state);
        }
        if (do_update > 0 && show_numbers) {
            if (_tick % text_update_rate == 0) {
                update_state.setString(std::to_string(do_update));
                update_state.setPosition(w.getSize().x - update_state.getLocalBounds().width - 5, w.getSize().y - 24);
            }
            w.draw(update_state);
        }
        if (show_fps) {
            if (_tick % fps_update_rate == 0) {
                //calculate frames per second
                now = std::chrono::system_clock::now();
                fps = (int) (1 / ((std::chrono::duration_cast<second>(now - previous_frame)).count() / fps_update_rate));
                fps_state.setString(std::to_string(fps));
                fps_state.setPosition(w.getSize().x - fps_state.getLocalBounds().width - 5, 5);
                previous_frame = now;
            }
            w.draw(fps_state);
        }
        w.display();
        if (_tick % fps_update_rate == 0) previous_frame = now;
        _tick++;
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
