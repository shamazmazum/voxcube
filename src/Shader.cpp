#include <fstream>
#include <iostream>
#include "Shader.h"

Shader::Shader (std::string filename, GLenum type) {
    this->shader = glCreateShader (type);

    std::ifstream input(filename);
    if (input.fail()) {
        throw std::runtime_error ("Cannot open a shader");
    }

    std::string shader;
    std::string line;
    GLint len;
    GLint log_len;
    const char *cstr;

    while (std::getline (input, line)) {
        shader += line;
        shader += '\n';
    }

    len = shader.length();
    cstr = shader.c_str();
    glShaderSource (this->shader, 1, &cstr, &len);
    glCompileShader (this->shader);
    glGetShaderiv(this->shader, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0) {
        char data[100];
		glGetShaderInfoLog(this->shader, 100, NULL, data);
        std::cout << std::string(data) << std::endl;
        throw std::runtime_error ("Cannot compile shader");
	}
}

Program::Program (Shader vertex, Shader frag) {
    GLint res;
    this->program = glCreateProgram ();

    glAttachShader (this->program, vertex.getShader());
    glAttachShader (this->program, frag.getShader());

    glLinkProgram (this->program);
    glGetProgramiv (this->program, GL_LINK_STATUS, &res);
    if (res == GL_FALSE) {
        throw std::runtime_error ("Cannot link program");
    }
}
