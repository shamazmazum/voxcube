#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/gl.h>

class ColorMap {
public:
    ColorMap (std::vector<glm::vec4> colormap);
    ~ColorMap() {
        glDeleteTextures (1, &this->textureID);
        glDeleteBuffers (1, &this->bufferID);
    }
    void bindColorMap () {
        glBindTexture (GL_TEXTURE_BUFFER, this->textureID);
    }
    size_t colors() {
        return this->count;
    }

private:
    size_t count;
    GLuint textureID;
    GLuint bufferID;
};
