#include "Application.h"

Application::Application (int w, int h, bool fullscreen) {
    if (SDL_Init (SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error ("Cannot initialize SDL");
    }

    this->window = std::make_unique<Window> (w, h, fullscreen);
    glClearColor (0.0, 0.0, 0.1, 0.0);
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::pair<int, int> winsize = this->window->windowSize ();
    person.setAspectRatio ((float)winsize.first / (float)winsize.second);
    person.setPosition (glm::vec3 (0.0f, 2.0f, 0.0f));

    Shader vert("shaders/world.vert", GL_VERTEX_SHADER);
    Shader frag("shaders/world.frag", GL_FRAGMENT_SHADER);
    this->program   = std::make_unique<Program> (vert, frag);
    this->proj      = this->program->uniformLocation ("proj");
    this->world2cam = this->program->uniformLocation ("world2cam");
    this->sampler   = this->program->uniformLocation ("sampler");

    this->model = std::make_unique<Model> ("skull.dat", 256, 256, 256, 1);

    SDL_EventState (SDL_MOUSEMOTION, SDL_DISABLE);
    SDL_SetRelativeMouseMode (SDL_TRUE);
}

Application::~Application() {
    SDL_Quit();
}

void Application::draw() {
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Sort planes
    glm::vec3 pos = this->person.position();
    this->model->sortPlanes (pos.z);

    this->program->use();
    // Set our "sampler" sampler to use Texture Unit 0
    glUniform1i (this->sampler, 0);
    // Projection matrix
    glm::mat4 project = person.projection();
    glUniformMatrix4fv (this->proj, 1, GL_FALSE, &project[0][0]);
    // World 2 Camera matrix
    glm::mat4 world2cam = person.world2Camera();
    glUniformMatrix4fv (this->world2cam, 1, GL_FALSE, &world2cam[0][0]);

    // Bind texture
    glActiveTexture (GL_TEXTURE0);
    this->model->bindTexture();

    glEnableVertexAttribArray(0);
    this->model->bindVertexBuffer();
    glVertexAttribPointer(0,         // layout
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glEnableVertexAttribArray(1);
    this->model->bindZCoords();
    glVertexAttribPointer(1,         // layout
                          1,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glDrawArraysInstanced (GL_TRIANGLE_STRIP, 0, 4, this->model->numQuads());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    this->window->redraw();
}

bool Application::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent (&event)) {
        switch (event.type) {
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
