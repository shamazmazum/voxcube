#pragma once
#include <string>
#include <vector>
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
    std::vector<glm::vec4> colorMap() {
        return this->colormap;
    }

private:
    glm::uvec3 dimensions;
    glm::bvec3 invertAxes;
    std::string datafile;
    unsigned int samplesize;
    std::vector<glm::vec4> colormap;
};
