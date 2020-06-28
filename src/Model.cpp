#include <fstream>
#include <vector>
#include "Model.h"

#define N 512

static const GLfloat quad_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
};

Model::Model (std::string density_map,
              int w, int h, int d,
              int bps) {
    std::ifstream input(density_map);
    if (input.fail()) {
        throw std::runtime_error ("Cannot open a model");
    }

    size_t samples = w * h * d;
    size_t size = samples * bps;
    char *buffer = new char [size];
    input.read (buffer, size);
    if (!input) {
        delete[] buffer;
        throw std::runtime_error ("Cannot load a model");
    }

    std::vector<float> texdata;
    float max = 1 << (8*bps);
    for (int i=0; i<samples; i++) {
        unsigned int val = 0;
        for (int j=0; j<bps; j++) {
            val += buffer[i*bps + j];
            val <<= 8;
        }
        val >>= 8;
        texdata.push_back ((float)val / max);
    }
    delete[] buffer;

    GLfloat delta = 2.0f/N;
    GLfloat z = -1.0f;
    for (int i=0; i<N; i++, z+=delta) {
        this->z.push_back (z);
    }

    glGenVertexArrays (1, &this->vertexarray);
    glBindVertexArray (this->vertexarray);

    // Quad
    glGenBuffers (1, &this->quadbuffer);
    glBindBuffer (GL_ARRAY_BUFFER, this->quadbuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (quad_data),
                  &quad_data[0], GL_STATIC_DRAW);

    // Z-coord
    // glGenBuffers (1, &this->zcoords);
    // glBindBuffer (GL_ARRAY_BUFFER, this->zcoords);
    // glBufferData (GL_ARRAY_BUFFER, sizeof (GLfloat) * this->z.size(),
    //               NULL, GL_STREAM_DRAW);
    glGenBuffers (1, &this->zcoords);
    glBindBuffer (GL_ARRAY_BUFFER, this->zcoords);
    glBufferData (GL_ARRAY_BUFFER, sizeof (GLfloat) * this->z.size(),
                  &this->z[0], GL_STATIC_DRAW);

    // Texture
    glGenTextures (1, &this->texture);
    glBindTexture (GL_TEXTURE_3D, this->texture);
    glTexImage3D (GL_TEXTURE_3D, 0, GL_RED, w, h, d,
                  0, GL_RED, GL_FLOAT, texdata.data());
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

GLuint Model::numQuads() {
    return N;
}

void Model::sortPlanes (GLfloat cameraZ) {
    // std::sort (this->z.begin(), this->z.end(),
    //            [=](GLfloat z1, GLfloat z2) {
    //                return std::abs (z1 - cameraZ) < std::abs (z2 - cameraZ);
    //            });
    // glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * this->z.size(),
    //               NULL, GL_STREAM_DRAW);
    // glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->z.size(),
    //                  &this->z[0]);
}
