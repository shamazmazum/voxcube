#pragma once
#include <string>
#include <memory>
#include <GL/gl.h>
#include "Window.h"
#include "Person.h"
#include "Model.h"
#include "ColorMap.h"
#include "Renderer.h"
#include "TextRenderer.h"

class Application {
public:
    Application (std::string cfgfile, int w = 0, int h = 0, bool fullscreen = true);
    ~Application();
    void draw();
    bool handleEvents();

private:
    std::unique_ptr<Window>       window;
    std::unique_ptr<Model>        model;
    std::unique_ptr<ColorMap>     colormap;
    std::unique_ptr<Renderer>     renderer;
    std::unique_ptr<TextRenderer> textRenderer;
    Person person;

    Uint32 ticks{0};
    Uint32 counter{0};
    Uint32 fps{0};
};
