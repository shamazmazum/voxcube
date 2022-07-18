#include <GL/gl.h>
#include "TextRenderer.h"
#include "Resources.h"

static const GLfloat uv_data[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
};

static const GLfloat vert_data[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f,
};

TextRenderer::TextRenderer (std::string font) {
    if (TTF_Init() != 0) {
        throw std::runtime_error (std::string ("Cannot initialize SDL_ttf: ")
                                  + TTF_GetError());
    }

    this->font = TTF_OpenFont (Resources::font (font).c_str(), 16);
    if (this->font == NULL) {
        throw std::runtime_error ("Cannot open font " + font + ": " +
                                  TTF_GetError());
    }

    Shader vert(Resources::shader ("text.vert"), GL_VERTEX_SHADER);
    Shader frag(Resources::shader ("text.frag"), GL_FRAGMENT_SHADER);

    this->program = std::make_unique<Program> (vert, frag);
    this->sampler = this->program->uniformLocation ("sampler");

    glGenTextures (1, &this->texture);
    glGenVertexArrays (1, &this->vertexArray);
    glGenBuffers (1, &this->vertexBuffer);
    glGenBuffers (1, &this->uvBuffer);

    glBindBuffer (GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (uv_data),
                  &uv_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vert_data),
                 &vert_data[0], GL_STATIC_DRAW);
}

void TextRenderer::drawText (std::string text, float x, float y) {
    SDL_Color fgcolor = {255, 255, 255, 255};
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_Surface *tmp = TTF_RenderText_Solid (this->font, text.c_str(), fgcolor);

    /*
     * KLUDGE: copy data from temporary structure to RGBA8888 format
     * to force surface->w * surface->format->BytesPerPixel ==
     * surface->pitch.
     */
    SDL_Surface *surface = SDL_ConvertSurface (tmp, format, 0);

    // Free temporary data
    SDL_FreeFormat (format);
    SDL_FreeSurface (tmp);

    // Use text shader
    this->program->use();

    // Setup text viewport
    glViewport (surface->w * x, surface->h * y, surface->w, surface->h);

    // Upload texture
    glBindTexture (GL_TEXTURE_2D, this->texture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA,
                  surface->w, surface->h,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Free Surface
    SDL_FreeSurface (surface);

    // Bind sampler
    glActiveTexture (GL_TEXTURE0);
    glUniform1i (this->sampler, 0);
    glBindTexture (GL_TEXTURE_2D, this->texture);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(0,         // layout
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glVertexAttribPointer(1,         // layout
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0); // array buffer offset

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}
