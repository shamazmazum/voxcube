#pragma once
#include <string>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

class Model {
public:
    Model (std::string density_map,
           glm::uvec3  dimensions,
           int         bps   = 1,
           glm::vec3   scale = glm::vec3 (1.0f));
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

    void setScaleUniform (GLuint scale) {
        glUniformMatrix4fv (scale, 1, GL_FALSE, &this->scale[0][0]);
    }

private:
    glm::mat4 scale;
    GLuint texture;
    GLuint quadbuffer;
    GLuint vertexarray;
};
