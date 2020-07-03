#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include "ConfigFile.h"

using namespace std::filesystem;

Configuration::Configuration (std::string filename) {
    Json::Value root;
    std::ifstream input(filename);

    if (input.fail()) {
        throw std::runtime_error ("Cannot open a configuration: " + filename);
    }

    input >> root;
    try {
        this->datafile = root["datafile"].asString();
        this->samplesize = root.get("samplesize", 1).asUInt();
        this->box.w = root["dimensions"]["w"].asUInt();
        this->box.h = root["dimensions"]["h"].asUInt();
        this->box.d = root["dimensions"]["d"].asUInt();
    } catch (const Json::LogicError &e) {
        std::cerr << "Cannot parse configuration: " << e.what() << std::endl;
        throw std::runtime_error ("Configuration error");
    }

    if (box.w == 0 ||
        box.h == 0 ||
        box.d == 0) {
        throw std::runtime_error (std::to_string (box.w) + "x" +
                                  std::to_string (box.h) + "x" +
                                  std::to_string (box.d) +
                                  ": invalid dimensions");
    }

    this->datafile = (path (filename).parent_path() / path (this->datafile)).string();
}
