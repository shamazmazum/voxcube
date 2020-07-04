#pragma once
#include "Model.h"
#include "Shader.h"
#include "Person.h"

class Renderer {
public:
    Renderer();
    void render (Person &person, std::unique_ptr<Model> &model);
    void incThreshold (float delta);
    void decThreshold (float delta);

private:
    std::unique_ptr<Program> program;
    GLuint proj;
    GLuint world2cam;
    GLuint thrID;
    GLuint sampler;
    float threshold{0.0f};
};
