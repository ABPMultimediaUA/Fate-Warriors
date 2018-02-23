#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <string>

class Shader{
    public:
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void use();
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
        void setMat4(const std::string &name, const glm::mat4 &mat);
    private:
        unsigned int ID;

        void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
