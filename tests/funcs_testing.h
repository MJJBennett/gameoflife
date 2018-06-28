#include <iostream>
#include <cassert>

#include "../include/funcs.h"

namespace testing {
    inline void funcs() {
        std::cout << "Running tests on " << "funcs.h" << std::endl;
        assert(split_reverse("something/else/image.png", '.') == "png");
        assert(split_reverse("", ',') == "");
        assert(split_reverse("..,..", ',') == "..");
        assert(split_reverse(",something", ',') == "something");
        assert(split_reverse("something,", ',') == "");
        std::cout << "All tests for " << "funcs.h" << " passed." << std::endl;
    }
}