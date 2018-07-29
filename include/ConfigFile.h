#ifndef CONWAYLIFE_CONFIGFILE_H
#define CONWAYLIFE_CONFIGFILE_H

#include "debug.h"
#include <fstream>
#include <map>

class ConfigFile {
public:
    explicit ConfigFile(std::string filename, bool auto_write = true) : _filename(filename) {
        write = debug::get_debugger("ConfigFile (" + filename + ')');
        auto f = std::ifstream(filename);
        if (!f.good()) {
            debug::err(write, "Could not open configuration file!");
            return;
        }
        if (auto_write) parse();
        f.close();
    }
    ~ConfigFile();
    void parse();
    const std::string & get_filename() const {return _filename;}
    const std::basic_string<char> & get(std::string var) const;
private:
    logger write;
    std::string _filename;
    std::map<std::string, std::string> configuration;
};


#endif //CONWAYLIFE_CONFIGFILE_H
