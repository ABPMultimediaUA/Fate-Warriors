#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

GLuint Shader::Programs[Shader_count];
GLuint Shader::Program=0;


Shader::Shader(){
    LoadShader(eSkybox, "src/Moose_Engine/Shaders/vertex_skybox.glsl", "src/Moose_Engine/Shaders/fragment_skybox.glsl");
    LoadShader(Default,"src/Moose_Engine/Shaders/vertex_prueba.glsl", "src/Moose_Engine/Shaders/fragment_prueba.glsl");
    LoadShader(sombras_proyectadas,"src/Moose_Engine/Shaders/vertex_proyeccion_sombras.glsl", "src/Moose_Engine/Shaders/fragment_proyeccion_sombras.glsl");
    LoadShader(texturas_menu,"src/Moose_Engine/Shaders/4.2.texture.vs", "src/Moose_Engine/Shaders/4.2.texture.fs");
    LoadShader(particulas,"src/Moose_Engine/Shaders/texture.vs", "src/Moose_Engine/Shaders/texture.fs");
}


void Shader::LoadShader(ShaderType type,const char* vertex_path, const char* fragment_path){
    //crear shaders
    GLuint ID;
    std::string vertex_Code;
    std::string fragment_Code;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {//cargar shaders
        vShaderFile.open(vertex_path);
        fShaderFile.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertex_Code   = vShaderStream.str();
        fragment_Code = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER:: El fichero de shader no se a leido correctamente" << std::endl;
    }
    const char* vShaderCode = vertex_Code.c_str();
    const char * fShaderCode = fragment_Code.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    //compilado y linkeo de shaders
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "Vertex_shader");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "Fragment_shader");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "Program_shader");
    Programs[type] = ID;
    std::cout<<"ID shader"<<(int)ID<<std::endl;
    // delete the shaders (estan linkeados a si que ya no nos sirven)
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(ShaderType type){ 
    Program=Programs[type];
    glUseProgram(Program);
}

void Shader::setBool(const std::string &name, bool value){         
    glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value){ 
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value){ 
    glUniform1f(glGetUniformLocation(Program, name.c_str()), value); 
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setvec3(const std::string &name, const glm::vec3 &vec){
    glUniform3fv(glGetUniformLocation(Program, name.c_str()),1,&vec[0]);
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
    glUniformMatrix4fv(glGetUniformLocation(Program, "modelView"), 1, GL_FALSE, &mv[0][0]);
    glm::mat4 mvp=_projection*_view*mat;
    glUniformMatrix4fv(glGetUniformLocation(Program, "MVP"), 1, GL_FALSE, &mvp[0][0]);
}
void Shader::setProjection(const glm::mat4 &mat){
    _projection=mat;
}
void Shader::setLuz(const glm::vec3 _i_luces[], unsigned int cantidad_luces){
    //pasamos cada uno de los parametros de las luces al vertex
    std::string sarray[4]={".Diffuse",".Specular",".Ambient",".Position"};
    std::string s;
    for(uint8_t cont;cont<4;cont++){
        s="Light["+std::to_string(cantidad_luces)+']'+sarray[cont];
        glUniform3fv(glGetUniformLocation(Program, s.c_str()),1,&_i_luces[cont][0]);
    }
    ++cantidad_luces;
    setInt("cantidad_luces",cantidad_luces);
    
}