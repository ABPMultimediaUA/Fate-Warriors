#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertex_Code;
    std::string fragment_Code;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertex_path);
        fShaderFile.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertex_Code   = vShaderStream.str();
        fragment_Code = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER:: El fichero de shader no se a leido correctamente" << std::endl;
    }
    const char* vShaderCode = vertex_Code.c_str();
    const char * fShaderCode = fragment_Code.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "Vertex_shader");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "Fragment_shader");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "Program_shader");
    // delete the shaders (estan linkeados a si que ya no nos sirven)
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::use(){ 
    glUseProgram(ID); 
}
void Shader::setBool(const std::string &name, bool value){         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value){ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value){ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::checkCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if (type != "Program_shader")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
void Shader::setView(const glm::mat4 &mat){
    _view = mat;
}
void Shader::setModel(const glm::mat4 &mat){
    glm::mat4 mv=_view*mat;
    glUniformMatrix4fv(glGetUniformLocation(ID, "modelView"), 1, GL_FALSE, &mv[0][0]);
    glm::mat4 mvp=_projection*_view*mat;
    glUniformMatrix4fv(glGetUniformLocation(ID, "MVP"), 1, GL_FALSE, &mvp[0][0]);
    glUniform1i(glGetUniformLocation(ID, "Material.Diffuse"),0);
    glUniform1i(glGetUniformLocation(ID, "Material.Specular"),1);
    glUniform1f(glGetUniformLocation(ID, "Material.Shininess"),1);
    glUniform3f(glGetUniformLocation(ID, "Light.Diffuse"),1,1,1);
    glUniform3f(glGetUniformLocation(ID, "Light.Specular"),1,1,1);
    glUniform3f(glGetUniformLocation(ID, "Light.Ambient"),1,1,1);
}
void Shader::setProjection(const glm::mat4 &mat){
    _projection=mat;
}