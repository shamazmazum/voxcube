#include <string>
#include <stdexcept>
#include "Window.h"

Window::Window (int w, int h, bool fullscreen) {
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute (SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute (SDL_GL_MULTISAMPLESAMPLES, 4);

    Uint32 flags = SDL_WINDOW_OPENGL;
    flags |= (fullscreen)? SDL_WINDOW_FULLSCREEN_DESKTOP: 0;
    this->window = SDL_CreateWindow ("voxcube",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     w, h, flags);
    if (this->window == NULL) {
        throw std::runtime_error (std::string ("Cannot create a window: ") +
                                  SDL_GetError());
    }

    this->context =  SDL_GL_CreateContext (this->window);
    if (this->context == NULL) {
        throw std::runtime_error (std::string ("Cannot create an OpenGL context: ") +
                                  SDL_GetError());
    }

    SDL_GetWindowSize (this->window, &this->w, &this->h);
    SDL_GL_SetSwapInterval (1);
}

Window::~Window () {
    if (this->context != NULL) {
        SDL_GL_DeleteContext (this->context);
    }

    if (this->window != NULL) {
        SDL_DestroyWindow (this->window);
    }
}
