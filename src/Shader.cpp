#include <fstream>
#include "Shader.h"

Shader::Shader (std::string filename, GLenum type) {
    this->shader = glCreateShader (type);

    std::ifstream input(filename);
    if (input.fail()) {
        throw std::runtime_error ("Cannot open a shader: " + filename);
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
        char data[200];
		glGetShaderInfoLog(this->shader, 200, NULL, data);
        throw std::runtime_error (std::string (data));
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
        throw std::runtime_error ("Cannot link a program");
    }
}
