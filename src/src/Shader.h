#ifndef SHADER_H
#define SHADER_H
 
#include <GL/glew.h>
#include <vector>
 
class Shader {
public:
    // Types of loaded shaders
    enum ShaderType {
        Default = 0,
        Skybox,
        Shader_count
    };
    // Loads shaders
    static void Init();
    // Sets current shader
    static void Use(ShaderType type);
    // Current shader
    static GLuint Program;
private:
    static void LoadShader(ShaderType type,const GLchar* vertexPath, const GLchar* fragmentPath);
    static GLuint Programs[Shader_count];
};
 
#endif /* SHADER_H */
