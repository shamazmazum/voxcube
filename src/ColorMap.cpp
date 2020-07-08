#include "ColorMap.h"

ColorMap::ColorMap (std::vector<glm::vec4> colormap) {
    this->count = colormap.size();

    glGenBuffers (1, &this->bufferID);
    glBindBuffer (GL_TEXTURE_BUFFER, this->bufferID);
    glBufferData (GL_TEXTURE_BUFFER, sizeof (glm::vec4) * this->count,
                  &colormap[0][0], GL_STATIC_DRAW);

    glGenTextures (1, &this->textureID);
    glBindTexture (GL_TEXTURE_BUFFER, this->textureID);
    glTexBuffer (GL_TEXTURE_BUFFER, GL_RGBA32F, this->bufferID);
}
