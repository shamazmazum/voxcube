#include <glm/ext.hpp>
#include "Person.h"

glm::mat4 rotate (float phi, float psi) {
    float cosphi = cos(phi);
    float sinphi = sin(phi);
    float cospsi = cos(psi);
    float sinpsi = sin(psi);

    glm::mat4 turn_right = glm::mat4 (
        cosphi, 0.0f, -sinphi, 0.0f,
          0.0f, 1.0f,    0.0f, 0.0f,
        sinphi, 0.0f,  cosphi, 0.0f,
          0.0f, 0.0f,    0.0f, 1.0f
        );

    glm::mat4 turn_up = glm::mat4 (
        1.0f,    0.0f,   0.0f, 0.0f,
        0.0f,  cospsi, sinpsi, 0.0f,
        0.0f, -sinpsi, cospsi, 0.0f,
        0.0f,    0.0f,   0.0f, 1.0f
        );

    return turn_up * turn_right;
}

glm::mat4 Person::world2Camera () {
    return rotate (this->phi, this->psi) *
        glm::translate (glm::mat4 (1.0f), -this->pos);
}

void Person::move (glm::vec3 delta) {
    glm::mat4 rotation = glm::transpose (rotate (this->phi, this->psi));
    glm::vec4 rotated = rotation * glm::vec4 (delta, 1.0f);

    this->pos += glm::vec3 (rotated);
}
