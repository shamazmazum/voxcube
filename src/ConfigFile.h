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
    glm::bvec3 axesInversion() {
        return this->invertAxes;
    }

private:
    glm::uvec3 dimensions;
    glm::bvec3 invertAxes;
    std::string datafile;
    unsigned int samplesize;
};
