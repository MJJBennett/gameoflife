#ifndef CONWAYLIFE_CONFIG_TESTING_H
#define CONWAYLIFE_CONFIG_TESTING_H

#include <iostream>
#include <cassert>

#include "../include/ConfigFile.h"

namespace testing {
    namespace config {
        inline void t_config() {
            std::cout << "Testing ConfigFile." << std::endl;
            ConfigFile cf("conf_test.txt");
            assert(cf.get("var1") == "");
            assert(cf.get("var2") == cf.get_filename());
            assert(cf.get("var3") == "val3");
            assert(cf.get("var4") == "val4");
            assert(cf.get("var5") == "val5");
        }
        inline void all() {
            t_config();
            std::cout << "All config tests passed." << std::endl;
        }
    }
}

#endif //CONWAYLIFE_CONFIG_TESTING_H
