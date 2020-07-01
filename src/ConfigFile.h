#pragma once
#include <string>

struct BoxSize {
    unsigned int w;
    unsigned int h;
    unsigned int d;
};

class Configuration {
public:
    Configuration (std::string filename);
    BoxSize dataSize() {
        return this->box;
    }
    std::string dataFile() {
        return this->datafile;
    }
    unsigned int sampleSize() {
        return this->samplesize;
    }

private:
    BoxSize box;
    std::string datafile;
    unsigned int samplesize;
};
