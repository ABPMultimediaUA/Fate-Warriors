#include "TMooseEngine.h"
#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TModelado.h"
#include "TAnimacion.h"
#include "TLuz.h"
#include "Shader.h"
#include <iostream>
#include <glm/ext.hpp>
#include <iostream>
#include "TNodo.h"

#include <string>
#include <sstream>
#include <fstream>

//OPEN GL 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*
#include "../../Interfaz/Motor.h"

void interfazTest(){
    Motor* interfaz_motor = Motor::Motor_GetInstance();
    
    const char cstr[] =  "Carne";
    //const char cstr2[] = "npc2";
    
    Camara* camara = interfaz_motor->crearCamara(true);
    //camara->mover(2, 0, 0);    
    iNodoLuz* luz = interfaz_motor->crearLuz(true, 1.0f, Vector3(1,1,1), Vector3(1,1,1), Vector3(1,1,1));

    //iNodoModelado* modelado1 = interfaz_motor->crearModelado(cstr, 3, 0, -10);
    //iNodoModelado* modelado2 = interfaz_motor->crearModelado(cstr2, 0, 0, -10);
    
    Player* _jugador = new Player(0, 10, 0, 10, )

    modelado1->mover(-3, 0, -10);
    modelado1->escalar(2,1,1);
    //modelado2->escalar(1,2,1);
    //camara->mover(-2,0,5);
   // camara->Camara_setProta(modelado1);
    camara->Camara_Update();
    while(interfaz_motor->ventana_abierta()){
        interfaz_motor->render();
    }
}
*/
void recorrerArbol(){

  

    //TGestorRecursos* resurseManajer = new TGestorRecursos();
    //resurseManajer->getRecursoModelo("Enemigo.obj");
    TMooseEngine* motor = TMooseEngine::get_instancia();
	
    TTransform* trans1 = motor->crearTransform();
	TTransform* trans2 = motor->crearTransform();
	TTransform* trans3 = motor->crearTransform();
    TTransform* trans4 = motor->crearTransform();
    TTransform* trans5 = motor->crearTransform();

	TLuz* luz = motor->crearLuz(glm::vec3(1,1,1),glm::vec3(1,1,1),glm::vec3(1,1,1));
    TCamara* camara = motor->crearCamara(true);
    const char cstr[] = "EscenarioSombras";
    TModelado* malla1 = motor->crearModelado(cstr);
    const char cstr2[] = "Anim_ataque_d1_npc2";
    TAnimacion* Animacion1 = motor->crearAnimacion(cstr2);

    /*const char cstr3[] = "Anim_idle_pistola_objetos";
    TAnimacion* Animacion2 = motor->crearAnimacion(cstr3);

   /* const char cstr4[] = "Anim_idle_ametrallador_objetos";
    TAnimacion* Animacion3 = motor->crearAnimacion(cstr4);*/

    //motor->stop_anim(cstr3);

  /*  const char cstr3[] = "Anim_ataque_d1_npc2";
    TAnimacion* Animacion2 = motor->crearAnimacion(cstr3);*/

    //trans1->escalar(0.5,0.25,0.5);
    trans1->trasladar(1,0,0);
    trans2->trasladar(1,0,-100000);//luz
    trans3->trasladar(0,5,25);//camara
    trans4->rotar(0,1,1,1);
    //trans5->rotar(0,1,0,10);
    

    TNodo* nodoTrans1 = motor->crearNodo(motor->nodoRaiz(), trans1);
    TNodo* nodoTrans2 = motor->crearNodo(motor->nodoRaiz(), trans2);
    //TNodo* nodoTrans5 = motor->crearNodo(motor->nodoRaiz(), trans3);
    TNodo* nodoTrans3 = motor->crearNodo(motor->nodoRaiz(), trans3);
    TNodo* nodoTrans4 = motor->crearNodo(nodoTrans1, trans4);
    
    TNodo* nodoMalla  = motor->crearNodo(nodoTrans4, Animacion1);
    TNodo* nodoMalla2  = motor->crearNodo(nodoTrans4, malla1);
    TNodo* nodoLuz    = motor->crearNodoLuz(nodoTrans2, luz);

    TNodo* nodoCamara = motor->crearNodoCamara(nodoTrans3, camara);
   

    TNodo* Escena=motor->nodoRaiz();
    //motor->borrarNodo(6);
    /*TNodo *RotaLuz= new TNodo();
    TNodo *RotaCam= new TNodo();
    TNodo* RotaCoche = new TNodo();
    Escena->agrega_hijo(RotaLuz);
    Escena->agrega_hijo(RotaCam);
    Escena->agrega_hijo(RotaCoche);
    TNodo* TraslaLuz=motor->crearNodo(motor->nodoRaiz(),trans1);
    TNodo* TraslaCam=motor->crearNodo(motor->nodoRaiz(),trans2);
    TNodo* TraslaCoche=motor->crearNodo(motor->nodoRaiz(),trans3);
    RotaLuz->agrega_hijo(TraslaLuz);
    RotaCam->agrega_hijo(TraslaCam);
    RotaCoche->agrega_hijo(TraslaCoche);
    TTransform *TransfRotaLuz=new TTransform();
    TTransform* TransfRotaCam=new TTransform();
    TTransform *TransfRotaCoche=new TTransform();
    RotaLuz->set_entidad(TransfRotaLuz);
    RotaCam->set_entidad(TransfRotaCam);
    RotaCoche->set_entidad(TransfRotaCoche);
    
    
    NLuz->set_entidad(EntLuz);
    NCam->set_entidad(EntCam);
    NChasis->set_entidad(MallaChasis);*/





    while(!motor->ventana_abierta()){

       //shader.use();
    
    //Escena->draw();
        // camera
        //
         /*   glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 100.0f);
        glm::mat4 view(glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::normalize(glm::cross(glm::normalize(glm::cross(glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 0.0f))),glm::vec3(0.0f,0.0f,-1.0f)))));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);*/

        // render the loaded model
        //glm::mat4 model=glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 1.75f, 50.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));	// it's a bit too big for our scene, so scale it down
        //shader.setMat4("model", model);
        motor->draw();


    }
    /*glm::mat4 algo=glm::mat4(1.0f);
    algo[0]=glm::vec4( 3.0, 4.0, 0.0, 1.0 );
    glm::mat4 algo2=glm::mat4(1.0f);
    algo2[1]=glm::vec4( 3.0, 7.0, 0.0, 1.0 );
    glm::mat4 algo3=algo*algo2;//a nivel de papel es algo2 * algo1
    std::cout<<algo[0][0]<<std::endl;
    /*int nViewport =motor->registrarViewport(x,y,alto,ancho);
    motor->setViewportActivoActivo(nViewport);
    int nCamara=motor->registrarCamara(nodoCamara);
    motor->setCamaraActiva(nCamara);
    int nLuz=motor->registrarLuz(nodoLuz);
    motor->setLuzActiva(nLuz);*/
    delete motor;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

float vertices[] = {
    // posiciones        // colores
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // abajo derecha
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bajo izquierda
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};    

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

int dibujarOpenGL(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MooseEngine", NULL, NULL);
    
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    //buffers
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    //vertex array object
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 


    glViewport(0, 0, 1280, 720);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    //leer los programas vertex y fragment shader
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::string vertex_Code;
    std::string fragment_Code;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    const GLchar* vertex_path = "src/Moose_Engine/Shaders/vertex_basic.glsl";
    const GLchar* fragment_path = "src/Moose_Engine/Shaders/fragment_basic.glsl";



    try {
        // Open files
        vShaderFile.open(vertex_path);
        fShaderFile.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vertex_Code = vShaderStream.str();
        fragment_Code = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar* vShaderCode = vertex_Code.c_str();
    const GLchar* fShaderCode = fragment_Code.c_str();
    

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //compilar fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //crear programa shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //comprobar que todo ha ido bien
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }    

    //asignar el programa shader y borramos los pequeños que ya han sido linkados
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 



    //TMooseEngine* motor=new TMooseEngine();
    
    while(!glfwWindowShouldClose(window)){
        //input
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        //motor->draw();
        //cosicas chulas    
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float colorSinValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexLocation = glGetUniformLocation(shaderProgram, "vertex_Color");
        glUniform4f(vertexLocation, 1-colorSinValue, 0.0f, colorSinValue, 1.0f);
        // ..:: Drawing code (in render loop) :: ..
        // 4. draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        //call events
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}

void main_tamanyofloat(){
    float** algo[200][2];
   /* algo[0][0]=1.0f;
    algo[0][1]=2.0f;
    algo[1][0]=1.5f;
    algo[1][1]=2.5f;*/
    float *result=0;
    std::cout<<sizeof(algo)<<"       "<<sizeof(result)<<std::endl; 
}


int main2(){
    //dibujarOpenGL();
    recorrerArbol();
    //interfazTest();
    return 0;
}