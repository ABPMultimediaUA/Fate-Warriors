#include <vector>
#include <glm/common.hpp>

#include <glad/glad.h>

class Shader;
 
class Billboards {
public:
    Billboards();
    void draw(Shader* _i_shader, glm::mat4 view, glm::mat4 projection);
    ~Billboards();
 
private:
    GLuint loadTexture(const GLchar* faces);
    std::vector<const GLchar*> faces;
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
};
