#include "Application.h"
#include "Resources.h"
#include "ConfigFile.h"

Application::Application (std::string cfgfile, int w, int h, bool fullscreen) {
    if (SDL_Init (SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error (std::string ("Cannot initialize SDL: ")
                                  + SDL_GetError());
    }

    this->window = std::make_unique<Window> (w, h, fullscreen);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::pair<int, int> winsize = this->window->windowSize ();
    person.setAspectRatio ((float)winsize.first / (float)winsize.second);
    person.setPosition (glm::vec3 (0.0f, 0.0f, 2.0f));

    Configuration cfg(cfgfile);
    BoxSize datasize = cfg.dataSize();
    this->model = std::make_unique<Model> (cfg.dataFile(),
                                           datasize.w,
                                           datasize.h,
                                           datasize.d,
                                           cfg.sampleSize());
    this->renderer = std::make_unique<Renderer> ();

    SDL_EventState (SDL_MOUSEMOTION, SDL_DISABLE);
    SDL_SetRelativeMouseMode (SDL_TRUE);
}

Application::~Application() {
    SDL_Quit();
}

void Application::draw() {
    this->renderer->render (this->person, this->model);
    this->window->redraw();
}

bool Application::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent (&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_O) {
                this->renderer->decThreshold (0.05f);
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_P) {
                this->renderer->incThreshold (0.05f);
            }
            break;
        case SDL_QUIT:
            return false;
        }
    }

    // Keyboard
    glm::vec3 pos_delta(0.0f);
    const Uint8 *keystate = SDL_GetKeyboardState (NULL);
    if (keystate[SDL_SCANCODE_W]) pos_delta.z -= 0.05;
    else if (keystate[SDL_SCANCODE_S]) pos_delta.z += 0.05;
    if (keystate[SDL_SCANCODE_A]) pos_delta.x -= 0.05;
    else if (keystate[SDL_SCANCODE_D]) pos_delta.x += 0.05;
    this->person.move (pos_delta);

    // Mouse
    int x,y;
    SDL_GetRelativeMouseState (&x, &y);
    this->person.turnRight (0.01*x);
    this->person.turnUp (0.01*y);

    return true;
}
