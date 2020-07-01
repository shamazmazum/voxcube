#include <filesystem>
#include <fstream>
#include <json/json.h>
#include "ConfigFile.h"

using namespace std::filesystem;

Configuration::Configuration (std::string filename) {
    Json::Value root;
    std::ifstream(filename) >> root;

    this->datafile = root["datafile"].asString();
    this->samplesize = root["samplesize"].asUInt();
    this->box.w = root["dimensions"]["w"].asUInt();
    this->box.h = root["dimensions"]["h"].asUInt();
    this->box.d = root["dimensions"]["d"].asUInt();

    this->datafile = (path (filename).parent_path() / path (this->datafile)).string();
}
