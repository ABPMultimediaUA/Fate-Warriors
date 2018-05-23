#include <vector>
#include <glm/common.hpp>

#include <glad/glad.h>

class Shader;
 
class Skybox {
public:
    Skybox();
    void draw(Shader* _i_shader, glm::mat4 view, glm::mat4 projection);
    ~Skybox();
 
private:
    /*Carga las imagenes del skybox*/
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    /*Vector con los nombres de las imagenes del skybox*/
    std::vector<const GLchar*> faces;
    /*Datos para el dibujado*/
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
};
