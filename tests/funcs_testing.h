#include <iostream>
#include <cassert>

#include "../include/funcs.h"

namespace testing {
    inline void funcs() {
        std::string res = split_reverse("something/else/image.png", '.');
        std::cout << "Testing split_reverse. Result of test (desires png): " << res << std::endl;
        assert(res == "png");
    }
}