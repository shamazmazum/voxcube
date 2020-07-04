#pragma once
#include <string>
#include <glm/glm.hpp>

class Configuration {
public:
    Configuration (std::string filename);
    glm::uvec3 dataSize() {
        return this->dimensions;
    }
    std::string dataFile() {
        return this->datafile;
    }
    unsigned int sampleSize() {
        return this->samplesize;
    }

private:
    glm::uvec3 dimensions;
    std::string datafile;
    unsigned int samplesize;
};
