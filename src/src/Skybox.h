#include <vector>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
 
class Skybox {
public:
    Skybox();
    void draw(glm::mat4 view, glm::mat4 projection);
    ~Skybox();
 
private:
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    std::vector<const GLchar*> faces;
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
};
