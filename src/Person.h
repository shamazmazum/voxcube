#pragma once
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Person {
public:
    glm::mat4 world2Camera ();

    void move (glm::vec3 delta);
    void turnRight (float delta) {
        this->phi += delta;
    }
    void turnUp (float delta) {
        this->psi = std::clamp (this->psi + delta,
                                -(float)M_PI_2,
                                 (float)M_PI_2);
    }
    glm::vec3 position () {
        return this->pos;
    }
    void setPosition (glm::vec3 pos) {
        this->pos = pos;
    }
    void setAspectRatio (float aspectRatio) {
        this->aspectRatio = aspectRatio;
    }
    void setFieldOfView (float fov) {
        this->fov = fov;
    }
    glm::mat4 projection() {
        return glm::perspective (this->fov, this->aspectRatio, 0.1f, 10.0f);
    }

private:
    glm::vec3 pos{};
    float phi{};
    float psi{};
    float aspectRatio{1.0f};
    float fov{glm::radians (70.0f)};
};
