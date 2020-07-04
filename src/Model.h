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
        glDeleteBuffers (1, &this->zcoords);
        glDeleteVertexArrays (1, &this->vertexarray);
        glDeleteTextures (1, &this->texture);
    }
    GLuint numQuads();

    void bindVertexBuffer() {
        glBindBuffer (GL_ARRAY_BUFFER, this->quadbuffer);
    }

    void bindZCoords() {
        glBindBuffer (GL_ARRAY_BUFFER, this->zcoords);
    }

    void bindTexture() {
        glBindTexture (GL_TEXTURE_3D, this->texture);
    }

    void sortPlanes (GLfloat cameraZ);

private:
    std::vector<GLfloat> z;
    GLuint texture;
    GLuint quadbuffer;
    GLuint zcoords;
    GLuint vertexarray;
};
