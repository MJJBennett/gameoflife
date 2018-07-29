#ifndef CONWAYLIFE_CONFIGFILE_H
#define CONWAYLIFE_CONFIGFILE_H

#include "debug.h"
#include <fstream>
#include <map>

//This class represents configuration options set in a file
class ConfigFile {
public:
    explicit ConfigFile(std::string filename, bool auto_write = true) : _filename(filename) {
        write = debug::get_debugger("ConfigFile (" + filename + ')');

        auto f = std::ifstream(filename);
        if (!f.good()) {
            debug::err(write, "Could not open configuration file!");
            return;
        }
        f.close();

        if (auto_write) parse();
        if (configuration.empty()) debug::warn(write, "No configuration options were set.");
    }

    //Run parse() to (re)load configuration options from _filename
    void parse();
    //Set filename if you want to switch to a different file (prior to calling parse())
    void set_filename(std::string&& filename) {_filename = std::move(filename);}
    void set_filename(std::string filename) {_filename = filename;}
    const std::string & get_filename() const {return _filename;}
    //Retrieves value for a variable
    const std::basic_string<char> & get(std::string var) const;
    const std::basic_string<char> & at(std::string var) const;
private:
    logger write;
    std::string _filename;
    std::map<std::string, std::string> configuration;
};


#endif //CONWAYLIFE_CONFIGFILE_H
