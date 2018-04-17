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
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    std::vector<const GLchar*> faces;
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
};
