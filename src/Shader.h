#pragma once
#include <string>
#include <GL/gl.h>

class Shader {
public:
    Shader (std::string filename, GLenum type);
    GLuint getShader() {
        return this->shader;
    }

private:
    GLuint shader;
};

class Program {
public:
    Program (Shader vertex, Shader fragment);
    ~Program() { glDeleteProgram (this->program); }
    void use() { glUseProgram (this->program); }
    GLuint uniformLocation (std::string name) {
        return glGetUniformLocation (this->program, name.c_str());
    }

private:
    GLuint program;
};
