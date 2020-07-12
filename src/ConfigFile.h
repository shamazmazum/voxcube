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
    glm::vec3 modelScale() {
        return this->scale;
    }
    std::vector<glm::vec4> colorMap() {
        return this->colormap;
    }

private:
    glm::uvec3   dimensions;
    glm::bvec3   invertAxes;
    glm::vec3    scale;
    std::string  datafile;
    unsigned int samplesize;
    std::vector<glm::vec4> colormap;
};
