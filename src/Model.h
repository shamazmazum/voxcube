#pragma once
#include <string>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

class Model {
public:
    Model (std::string density_map,
           glm::uvec3 dimensions,
           int bps);
    ~Model() {
        glDeleteBuffers (1, &this->quadbuffer);
        glDeleteVertexArrays (1, &this->vertexarray);
        glDeleteTextures (1, &this->texture);
    }

    void bindVertexBuffer() {
        glBindBuffer (GL_ARRAY_BUFFER, this->quadbuffer);
    }

    void bindTexture() {
        glBindTexture (GL_TEXTURE_3D, this->texture);
    }

private:
    GLuint texture;
    GLuint quadbuffer;
    GLuint vertexarray;
};
