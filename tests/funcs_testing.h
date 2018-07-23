#include <iostream>
#include <cassert>

#include "../include/funcs.h"

namespace testing {
    namespace funcs {
        inline void t_split_reverse() {
            assert(split_reverse("something/else/image.png", '.') == "png");
            assert(split_reverse("", ',') == "");
            assert(split_reverse("..,..", ',') == "..");
            assert(split_reverse(",something", ',') == "something");
            assert(split_reverse("something,", ',') == "");
        }
        inline void t_split() {
            assert(split("something.something else", '.') == "something");
            assert(split(".this is real", '.') == "");
            assert(split("this is not", 'q') == "this is not");
        }
        inline void all() {
            std::cout << "Running tests on " << "funcs.h" << std::endl;
            std::cout << "Testing split()" << std::endl;
            t_split();
            std::cout << "Testing split_reverse()" << std::endl;
            t_split_reverse();
            std::cout << "All tests for " << "funcs.h" << " passed." << std::endl;
        }
    }

}