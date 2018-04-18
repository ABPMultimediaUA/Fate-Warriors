#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <string>


// Types of loaded shaders
enum ShaderType {
    Default = 0,
    eSkybox,
    Shader_count
};


class Shader{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        void LoadShader(ShaderType type,const char* vertexPath, const char* fragmentPath);
        void use(ShaderType type);
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
        void setMat4(const std::string &name, const glm::mat4 &mat);
        void setvec3(const std::string &name, const glm::vec3 &vec);
        void setView(const glm::mat4 &mat);
        void setModel(const glm::mat4 &mat);
        void setProjection(const glm::mat4 &mat);

        inline glm::mat4 getProjection(){ return _projection;};
        inline glm::mat4 getView(){ return _view;};

        static GLuint Program;


    private:

        static GLuint Programs[Shader_count];

        unsigned int ID;
        glm::mat4 _view,_projection;
        void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
