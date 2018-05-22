#include "Image.h"
#include "SOIL.h"
#include "src/Moose_Engine/src/Shader.h"
#include <iostream>


//constructor unico que recibe 4 rutas independientemente de las que se usen en cada tipo de imagen
Image::Image(Shader* shader, int numTexturas, const char* ruta, const char* ruta2, const char* ruta3, const char* ruta4, float x, float y, float width, float height)
    : shader(shader)
{
    _selected = 1;
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    init();
    //si se trata una imagen de menos de 4 rutas, se usan unicamente las rutas necesarias y se cargan el numero de texturas necesario
    switch (numTexturas){
        case 1: load_texture(ruta);
                break;

        case 2: load_texture(ruta);
                load_texture2(ruta2);
                break;
        
        case 3: load_texture(ruta);
                load_texture2(ruta2);
                load_texture3(ruta3);
                break;
        
        case 4: load_texture(ruta);
                load_texture2(ruta2);
                load_texture3(ruta3);
                load_texture4(ruta4);
                break;
    }
}

void Image::setSelected(int selected){
    _selected = selected;
}

bool Image::getSelected(){
    return _selected;
}

Image::~Image(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Image::init()
{
    glEnable(GL_BLEND);
    //posicionamiento de los vertices que conforman el rectangulo 2d de la imagen
    //este init utiliza las variables de anchura y altura pasadas en la creacion para ajustar las posiciones de los
    //vertices
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         _x + _width,  _y,          0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
         _x + _width, _y - _height, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // bottom right
         _x, _y - _height,          0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
         _x,  _y,                   0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //manejo de buffers y arrays, basado en el tutorial "basic textures" de learnopengl
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

void Image::load_texture(const char* ruta){
    
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
    //nrChannels = 4;
    //lectura de datos de textura usando la libreria de SOIL
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
    //cargamos los datos de la textura en la variable ID
    glUniform1i(glGetUniformLocation(Shader::Program, "texture1"), ID);
    
}

void Image::load_texture2(const char* ruta){
    
    glGenTextures(1, &ID2);
    glBindTexture(GL_TEXTURE_2D, ID2); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    
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

    glUniform1i(glGetUniformLocation(Shader::Program, "texture1"), ID2);
}

void Image::load_texture3(const char* ruta){
    glGenTextures(1, &ID3);
    glBindTexture(GL_TEXTURE_2D, ID3); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
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

    glUniform1i(glGetUniformLocation(Shader::Program, "texture1"), ID3);
}

void Image::load_texture4(const char* ruta){
    glGenTextures(1, &ID4);
    glBindTexture(GL_TEXTURE_2D, ID4); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
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

    glUniform1i(glGetUniformLocation(Shader::Program, "texture1"), ID4);
}

// Render image
void Image::Draw()
{
    //activamos el shader especifico para visualizar imagenes en 2D
    shader->use(texturas_menu);
    
    glUniform1f(glGetUniformLocation(Shader::Program, "width"), _width);
    
    glDepthMask(false);

    //funcion de fundido para conseguir las transparencias de las imagenes png
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTexture(GL_TEXTURE0);

    //en funcion de que textura hay que seleccionar, se bindea la ID de las 4 disponibles 
    //nota: cada ID se crea en su correspondiente funcion loadtexture
    switch(_selected){
        case 1: glBindTexture(GL_TEXTURE_2D, ID);
                break;
        
        case 2: glBindTexture(GL_TEXTURE_2D, ID2);
                break;

        case 3: glBindTexture(GL_TEXTURE_2D, ID3);
                break;

        case 4: glBindTexture(GL_TEXTURE_2D, ID4);
                break;
    }
        
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glDepthMask(true);
}

//ajusta el tamanyo de la imagen en funcion del parametro (0 = 0% || 1 = 100%) esto se consigue
//reasignando los vertices de nuevo para cambiar sus posiciones
void Image::setSizeX(float sizeX){
    _sizeX = sizeX;
    float auxWidth = _width;
    _width = auxWidth * _sizeX;

    float vertices[] = {
        // positions          // colors           // texture coords
         _x + _width,  _y,          0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
         _x + _width, _y - _height, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // bottom right
         _x, _y - _height,          0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
         _x,  _y,                   0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f // top left 
    };
        
    _width = auxWidth; 

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