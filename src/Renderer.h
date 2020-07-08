#pragma once
#include <algorithm>
#include <memory>
#include <glm/glm.hpp>
#include "ColorMap.h"
#include "Model.h"
#include "Shader.h"
#include "Person.h"

class Renderer {
public:
    Renderer (glm::bvec3 invertAxes = glm::bvec3 (false, false, false));
    void render (Person                    &person,
                 std::unique_ptr<Model>    &model,
                 std::unique_ptr<ColorMap> &colormap);
    void incThreshold (float delta) {
        this->threshold = std::clamp (this->threshold + delta, 0.0f, 1.0f);
    }
    void decThreshold (float delta) {
        this->threshold = std::clamp (this->threshold - delta, 0.0f, 1.0f);
    }

private:
    std::unique_ptr<Program> program;
    GLuint proj;
    GLuint world2cam;
    GLuint thrID;
    GLuint sampler;
    GLuint samplerCM;
    GLuint colors;
    GLuint invertID;
    GLuint nplanes;
    glm::bvec3 invertAxes;
    float threshold{0.0f};
};
