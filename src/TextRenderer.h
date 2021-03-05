#pragma once
#include <memory>
#include <SDL2/SDL_ttf.h>
#include "Shader.h"

class TextRenderer {
public:
    TextRenderer (std::pair<int, int> window_size, std::string font);
    ~TextRenderer () {
        TTF_CloseFont (this->font);
        TTF_Quit();
        glDeleteTextures (1, &this->texture);
        glDeleteBuffers (1, &this->vertexBuffer);
        glDeleteBuffers (1, &this->uvBuffer);
        glDeleteVertexArrays (1, &this->vertexArray);
    }
    void drawText (std::string text, float x, float y);

private:
    TTF_Font *font;
    std::pair<int, int> window_size;
    std::unique_ptr<Program> program;
    GLuint sampler;
    GLuint texture;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint vertexArray;
};
