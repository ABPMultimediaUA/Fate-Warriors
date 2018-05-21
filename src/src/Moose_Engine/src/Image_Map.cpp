/* Aprendido de paginas como: 
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
https://www.gamedev.net/forums/topic/637183-how-to-create-minimap-sdlopengl/
https://learnopengl.com/Getting-started/Textures
https://stackoverflow.com/questions/1733488/terrain-minimap-in-opengl
https://www.leadwerks.com/community/topic/4487-what-method-for-adding-a-mini-map/
...
*/

#include "Image_Map.h"
#include "SOIL.h"
#include "src/Moose_Engine/src/Shader.h"
#include <iostream>

Image_Map::Image_Map(Shader* shader, GLuint ruta, float x, float y, float width, float height)
    : shader(shader)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    init();
    ID = ruta;
}


Image_Map::~Image_Map(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Image_Map::setTextureposition(float x, float y, float rotacion){
   
    _x = x;
    _y = y;
    _rotacion = rotacion;

    glm::vec2 posicion_en_pantalla = glm::vec2(_x,_y) - glm::vec2(420,560); // X, Y es la posicion en la pantalla se transforma la posicion a una posicion de opengl
    posicion_en_pantalla /= glm::vec2(420,560);                             // Se divide para tener la coordenada en pantalla
                                                                
    glm::vec2 escala_en_pantalla = glm::vec2(_width,_height); // Se hace el mismo procedimiento en la escala (transformar de escala con respecto al tamaño a escala para opengl)
    escala_en_pantalla /= glm::vec2(420,560);


    float _x = posicion_en_pantalla.x;
    float _y = posicion_en_pantalla.y;
    float _width = escala_en_pantalla.x / 2;
    float _height = escala_en_pantalla.y / 2;
    
    
     float vertices[] = {
                  // positions                    // colors       // texture coords
         _x + _width, _y + _height, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,    // arriba a la derecha
         _x + _width, _y - _height, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,    // abajo a la derecha
         _x - _width, _y - _height, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,    // abajo a la izquierda
         _x - _width, _y + _height, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f     // arriba a la izquierda
    };


    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}


void Image_Map::init()
{

    glEnable(GL_BLEND); //Activo para la opacidad de las imagenes

    glm::vec2 posicion_en_pantalla = glm::vec2(_x,_y) - glm::vec2(420,560); // X, Y es la posicion en la pantalla se transforma la posicion a una posicion de opengl
    posicion_en_pantalla /= glm::vec2(420,560);                             // Se divide para tener la coordenada en pantalla
                                                                
    glm::vec2 escala_en_pantalla = glm::vec2(_width,_height); // Se hace el mismo procedimiento en la escala (transformar de escala con respecto al tamaño a escala para opengl)
    escala_en_pantalla /= glm::vec2(420,560);
    
    float _x = posicion_en_pantalla.x;
    float _y = posicion_en_pantalla.y;
    float _width = escala_en_pantalla.x / 2;
    float _height = escala_en_pantalla.y / 2;
    
    
    float vertices[] = {
                  // positions                    // colors       // texture coords
         _x + _width, _y + _height, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,    // arriba a la derecha
         _x + _width, _y - _height, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,    // abajo a la derecha
         _x - _width, _y - _height, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,    // abajo a la izquierda
         _x - _width, _y + _height, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f     // arriba a la izquierda
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}


void Image_Map::update_rotacion(){
  //  std::cout << _rotacion << "rotacion \n";
    glUniform1f(glGetUniformLocation(Shader::Program, "rotacion_a"), _rotacion);    
}


void Image_Map::Draw()
{
    //Desactivar la mascara de profundidad para situarlo en pantalla
    glDepthMask(false);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Devolverlo a como estaba previamente para dibujar el resto de elementos
    glDepthMask(true);
}