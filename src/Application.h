#pragma once
#include <string>
#include <GL/gl.h>
#include "Window.h"
#include "Person.h"
#include "Model.h"
#include "Shader.h"

class Application {
public:
    Application (std::string cfgfile, int w = 0, int h = 0, bool fullscreen = true);
    ~Application();
    void draw();
    bool handleEvents();

private:
    std::unique_ptr<Window>  window;
    std::unique_ptr<Program> program;
    std::unique_ptr<Model>   model;

    Person person;
    GLuint proj;
    GLuint world2cam;
    GLuint thrID;
    GLuint sampler;
    float threshold{0.0f};
};
