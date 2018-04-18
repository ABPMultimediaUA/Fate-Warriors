#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <string>
#include <vector>
class Shader{
    public:
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        ~Shader()=default;
        void use();
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
        void setMat4(const std::string &name, const glm::mat4 &mat);
        void setvec3(const std::string &name, const glm::vec3 &vec);
        void setView(const glm::mat4 &mat);
        void setModel(const glm::mat4 &mat);
        void setProjection(const glm::mat4 &mat);
        void setLuz(const glm::vec3 _i_luces[], unsigned int cantidad_luces);
    private:
        unsigned int ID;
        glm::mat4 _view,_projection;
        void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
