#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <string>

// Types of loaded shaders
enum ShaderType {
    Default = 0,
    eSkybox,
    sombras_proyectadas,
    texturas_menu,
    particulas,
    Shader_count
};

//el codigo de esta clase esta basado en el codigo de learnopengl
class Shader{
    public:
        Shader();
        ~Shader()=default;

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
        void setLuz(const glm::vec3 _i_luces[], unsigned int cantidad_luces);
        static GLuint Program;

        inline glm::mat4 getProjection(){ return _projection;};
        inline glm::mat4 getView(){ return _view;};
        inline bool check_program(ShaderType type){if(Programs[type]==Program) return true; else return false;}
        
    private:

        static GLuint Programs[Shader_count];
        glm::mat4 _view,_projection;
        void checkCompileErrors(unsigned int shader, std::string type);
        glm::vec3 posicion_luz;

};

#endif
