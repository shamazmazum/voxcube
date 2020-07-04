#include <stdexcept>
#include <GL/gl.h>
#include "Resources.h"
#include "Renderer.h"

Renderer::Renderer() {
    Shader vert(Resources::shader ("world.vert"), GL_VERTEX_SHADER);
    Shader frag(Resources::shader ("world.frag"), GL_FRAGMENT_SHADER);

    this->program   = std::make_unique<Program> (vert, frag);
    this->proj      = this->program->uniformLocation ("proj");
    this->world2cam = this->program->uniformLocation ("world2cam");
    this->sampler   = this->program->uniformLocation ("sampler");
    this->thrID     = this->program->uniformLocation ("threshold");
}

void Renderer::render (Person &person, std::unique_ptr<Model> &model) {
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Sort planes
    glm::vec3 pos = person.position();
    model->sortPlanes (pos.z);

    this->program->use();
    // Set our "sampler" sampler to use Texture Unit 0
    glUniform1i (this->sampler, 0);
    // Projection matrix
    glm::mat4 project = person.projection();
    glUniformMatrix4fv (this->proj, 1, GL_FALSE, &project[0][0]);
    // World 2 Camera matrix
    glm::mat4 world2cam = person.world2Camera();
    glUniformMatrix4fv (this->world2cam, 1, GL_FALSE, &world2cam[0][0]);
    // Density threshold
    glUniform1f (this->thrID, this->threshold);

    // Bind texture
    glActiveTexture (GL_TEXTURE0);
    model->bindTexture();

    glEnableVertexAttribArray(0);
    model->bindVertexBuffer();
    glVertexAttribPointer(0,         // layout
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glEnableVertexAttribArray(1);
    model->bindZCoords();
    glVertexAttribPointer(1,         // layout
                          1,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glDrawArraysInstanced (GL_TRIANGLE_STRIP, 0, 4, model->numQuads());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
