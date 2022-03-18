#include <stdexcept>
#include <GL/gl.h>
#include "Resources.h"
#include "Renderer.h"

#define N 512

Renderer::Renderer (glm::bvec3 invertAxes) {
    Shader vert(Resources::shader ("world.vert"), GL_VERTEX_SHADER);
    Shader frag(Resources::shader ("world.frag"), GL_FRAGMENT_SHADER);

    this->program   = std::make_unique<Program> (vert, frag);
    this->proj      = this->program->uniformLocation ("proj");
    this->world2cam = this->program->uniformLocation ("world2cam");
    this->sampler   = this->program->uniformLocation ("sampler");
    this->samplerCM = this->program->uniformLocation ("colormap");
    this->colors    = this->program->uniformLocation ("colors");
    this->mulID     = this->program->uniformLocation ("multiplier");
    this->thrID     = this->program->uniformLocation ("threshold");
    this->invertID  = this->program->uniformLocation ("invert_axes");
    this->nplanes   = this->program->uniformLocation ("nplanes");
    this->scale     = this->program->uniformLocation ("scale");

    this->invertAxes = invertAxes;
}

void Renderer::render (Person                    &person,
                       std::unique_ptr<Model>    &model,
                       std::unique_ptr<ColorMap> &colormap) {
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    this->program->use();
    // Set our sampler to use Texture Unit 0
    glUniform1i (this->sampler, 0);

    // Set our colormap sampler to use Texture Unit 1
    glUniform1i (this->samplerCM, 1);

    // Number of colors
    glUniform1i (this->colors, colormap->colors());

    // Projection matrix
    glm::mat4 project = person.projection();
    glUniformMatrix4fv (this->proj, 1, GL_FALSE, &project[0][0]);

    // World 2 Camera matrix
    glm::mat4 world2cam = person.world2Camera();
    glUniformMatrix4fv (this->world2cam, 1, GL_FALSE, &world2cam[0][0]);

    // Density threshold
    glUniform1f (this->thrID, this->threshold);

    // Density multiplier
    glUniform1f (this->mulID, this->multiplier);

    // Axes direction
    glUniform3ui (this->invertID,
                  this->invertAxes.x,
                  this->invertAxes.y,
                  this->invertAxes.z);

    // Number of planes
    glUniform1ui (this->nplanes, N);

    // Set scale matrix
    model->setScaleUniform (this->scale);

    // Bind texture
    glActiveTexture (GL_TEXTURE0);
    model->bindTexture();

    // Bind colormap
    glActiveTexture (GL_TEXTURE0 + 1);
    colormap->bindColorMap();

    glEnableVertexAttribArray(0);
    model->bindVertexBuffer();
    glVertexAttribPointer(0,         // layout
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glVertexAttribDivisor(0, 0);
    glDrawArraysInstanced (GL_TRIANGLE_STRIP, 0, 4, N);
    glDisableVertexAttribArray(0);
}
