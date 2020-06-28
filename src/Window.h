#pragma once
#include <utility>
#include <SDL2/SDL.h>

class Window {
public:
    Window (int w, int h, bool fullscreen);
    ~Window();
    std::pair<int, int> windowSize() {
        return std::pair<int, int> (this->w, this->h);
    }
    void redraw() {
        SDL_GL_SwapWindow (this->window);
    }

private:
    SDL_Window *window;
    SDL_GLContext context;
    int w, h;
};
