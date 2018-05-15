#include "Mapa.h"
#include "SOIL.h"
#include "Shader.h"
#include "Image_Map.h"
#include "glm/ext.hpp"
#include <iostream>



Mapa::Mapa(Shader* shader)
    : shader(shader)
{
    init();
    load_texture("Skybox_Images/cesped.png", Enum_Mapa);
    load_texture("Skybox_Images/vegeta.PNG", Enum_Llave);
    load_texture("Skybox_Images/vegeta.PNG", Enum_Player);
   
}


Mapa::~Mapa(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Mapa::eliminar_elemento_mapa(Image_Map* objeto_a_eliminar){
/*
    std::vector<GameObject_Visual>::iterator it;
    it = std::find(elementos_menu.begin(), elementos_menu.end(), objeto_a_eliminar);
    if ( it != elementos_menu.end()){
        elementos_menu.erase(it);
        delete objeto_a_eliminar;
    }
    */
}



Image_Map* Mapa::anyadir_elemento_al_mapa(float x, float y, Texture_ID_Map tipo){
    Image_Map* objeto_nuevo = new Image_Map(shader, x, y, 1, 1);
    elementos_menu.push_back(objeto_nuevo);
    return objeto_nuevo;
}


// Render all particles
void Mapa::Draw()
{    
        // Use additive blending to give it a 'glow' effect
    glDepthMask(false);
    // Don't forget to reset to default blending mode
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->use(particulas);
   
    for (int a =0; a < elementos_menu.size(); a++)
    {
        elementos_menu[a]->Draw();
       
    }
    // Don't forget to reset to default blending mode
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(true);

}

void Mapa::load_texture(const char* ruta, Texture_ID_Map elemento) {
  
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
  //  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = SOIL_load_image(ruta, &width, &height, 0, SOIL_LOAD_RGBA);
    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data);

    Imagenes[elemento] = ID;
   glUniform1i(glGetUniformLocation(Shader::Program, "sprite"), 0);
    
}



void Mapa::init()
{
        glEnable(GL_BLEND);

        float _x = 0.5;
        float _y = 0.5;
        float _width = 0.5;
        float _height = 0.5;


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f // top left 
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

