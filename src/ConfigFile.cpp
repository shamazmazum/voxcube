#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <algorithm>
#include "ConfigFile.h"

using namespace std::filesystem;

Configuration::Configuration (std::string filename) {
    Json::Value root;
    std::ifstream input(filename);

    if (input.fail()) {
        throw std::runtime_error ("Cannot open a configuration: " + filename);
    }

    try {
        input >> root;
        this->datafile = root["datafile"].asString();
        this->samplesize = root.get("samplesize", 1).asUInt();
        this->dimensions = glm::uvec3 (root["dimensions"]["w"].asUInt(),
                                       root["dimensions"]["h"].asUInt(),
                                       root["dimensions"]["d"].asUInt());
        this->invertAxes = glm::bvec3 (root["invert"]["x"].asBool(),
                                       root["invert"]["y"].asBool(),
                                       root["invert"]["z"].asBool());
        for (const auto& iter : root["colormap"]) {
            this->colormap.push_back (glm::vec4 (iter[0].asFloat(),
                                                 iter[1].asFloat(),
                                                 iter[2].asFloat(),
                                                 iter[3].asFloat()));
        }

        std::sort (colormap.begin(), colormap.end(),
                   [](glm::vec4 x, glm::vec4 y) {return x.a < y.a;});
    } catch (const Json::LogicError &e) {
        std::cerr << "Cannot parse configuration: " << e.what() << std::endl;
        throw std::runtime_error ("Invalid configuration data");
    } catch (const Json::RuntimeError &e) {
        std::cerr << "Cannot parse configuration: " << e.what() << std::endl;
        throw std::runtime_error ("Configuration: malformed JSON");
    }

    if (this->dimensions.x == 0 ||
        this->dimensions.y == 0 ||
        this->dimensions.z == 0) {
        throw std::runtime_error (std::to_string (this->dimensions.x) + "x" +
                                  std::to_string (this->dimensions.y) + "x" +
                                  std::to_string (this->dimensions.z) +
                                  ": invalid dimensions");
    }

    this->datafile = (path (filename).parent_path() / path (this->datafile)).string();
}
