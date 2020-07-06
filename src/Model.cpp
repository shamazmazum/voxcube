#include <fstream>
#include <vector>
#include "Model.h"

static const GLfloat quad_data[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f,
};

Model::Model (std::string density_map,
              glm::uvec3 dimensions,
              int bps) {
    std::ifstream input(density_map);
    if (input.fail()) {
        throw std::runtime_error ("Cannot open a model: " + density_map);
    }

    size_t samples = dimensions.x * dimensions.y * dimensions.z;
    size_t size = samples * bps;
    char *buffer = new char [size];
    input.read (buffer, size);
    if (!input) {
        delete[] buffer;
        throw std::runtime_error ("Cannot load a model: " + density_map);
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

    glGenVertexArrays (1, &this->vertexarray);
    glBindVertexArray (this->vertexarray);

    // Quad
    glGenBuffers (1, &this->quadbuffer);
    glBindBuffer (GL_ARRAY_BUFFER, this->quadbuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (quad_data),
                  &quad_data[0], GL_STATIC_DRAW);

    // Texture
    glGenTextures (1, &this->texture);
    glBindTexture (GL_TEXTURE_3D, this->texture);
    glTexImage3D (GL_TEXTURE_3D, 0, GL_RED,
                  dimensions.x, dimensions.y, dimensions.z,
                  0, GL_RED, GL_FLOAT, texdata.data());
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
