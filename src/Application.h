#pragma once
#include <string>
#include <memory>
#include <GL/gl.h>
#include "Window.h"
#include "Person.h"
#include "Model.h"
#include "Renderer.h"

class Application {
public:
    Application (std::string cfgfile, int w = 0, int h = 0, bool fullscreen = true);
    ~Application();
    void draw();
    bool handleEvents();

private:
    std::unique_ptr<Window>   window;
    std::unique_ptr<Model>    model;
    std::unique_ptr<Renderer> renderer;
    Person person;
};
