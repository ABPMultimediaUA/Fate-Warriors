#include "TMooseEngine.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TLuz.h"
#include "TModelado.h"
#include "TGestorRecursos.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct Mapeado{//declaracion de los parametros
    bool activa;
    TNodo* nodo;
};
TMooseEngine::TMooseEngine(){
    init_opengl();
    uint16_t _contadorIDEntidad = 0;
    _n_camaras=2;
    _n_c_actual=0;
    _n_l_actual=0;
    _n_luces=0;
    _gestorRecursos = TGestorRecursos::get_instancia();
    TNodo* nodo = new TNodo(_contadorIDEntidad,nullptr);
    _escena = nodo;
    _mapping_camaras = new Mapeado[_n_camaras];
    _mapping_luces   = new Mapeado[_n_luces];
    _shader = new Shader("Shaders/vertex_prueba.glsl", "Shaders/fragment_prueba.glsl");
    
}
TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    delete _mapping_luces;
    delete _mapping_camaras;
    delete _shader;
    _contadorIDEntidad=0;
    glfwTerminate();

}
void TMooseEngine::init_opengl(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1280, 720, "MooseEngine", NULL, NULL);
   

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
   
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }  
    //glEnable(GL_DEPTH_TEST);
    glViewport(0,0,1280,720);

}
TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    nodo->set_entidad(ent);
    padre->agrega_hijo(nodo);
    ++_contadorIDEntidad;
    return nodo;
}
TNodo* TMooseEngine::crearNodoCamara(TNodo *padre, TEntidad *ent){
    _mapping_camaras[_n_c_actual]={true,crearNodo(padre,ent)};
    ++_n_c_actual;
}
TNodo* TMooseEngine::crearNodoLuz(TNodo *padre, TEntidad *ent){
    _mapping_luces[_n_l_actual]={true,crearNodo(padre,ent)};
    ++_n_l_actual;
}

TTransform* TMooseEngine::crearTransform(){
    TTransform* transform = new TTransform();
    return transform;
}

TCamara* TMooseEngine::crearCamara(){
    TCamara* camara = new TCamara();
    return camara;
}

TLuz* TMooseEngine::crearLuz(){
    TLuz* luz = new TLuz();
    return luz;
}

TModelado* TMooseEngine::crearModelado(char* _i_path){
    TModelado* malla = new TModelado(_i_path);
    //_gestorRecursos->getRecursoMalla(fichero);
    return malla;
}
void TMooseEngine::clear(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(
        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void TMooseEngine::draw(){
    clear();
    _shader->use();
    drawCamaras();
    drawLuces();
    _escena->draw(_shader);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::drawLuces(){
    u_int16_t cont = 0;
    std::stack<glm::mat4> pila_matriz_luz;
    for(uint16_t i = 0; i < _n_luces; i++){
        if(_mapping_luces[i].activa){
            TNodo* this_node = _mapping_luces[i].nodo;
            while(this_node->get_padre()!=nullptr){
                pila_matriz_luz.push(this_node->get_entidad()->get_matriz());
                this_node = this_node->get_padre();
                cont++;
            }

            for(u_int16_t a = 0; a < cont; a++){
               matriz_luz = matriz_luz * pila_matriz_luz.top();
               pila_matriz_luz.pop();
            }
        }
    }
}

void TMooseEngine::drawCamaras(){
    u_int16_t cont = 0;
    std::stack<glm::mat4> pila_matriz_camara;
    for(uint16_t i = 0; i < _n_luces; i++){
        if(_mapping_camaras[i].activa){
            TNodo* this_node = _mapping_camaras[i].nodo;
            while(this_node->get_padre()!=nullptr){
                pila_matriz_camara.push(this_node->get_entidad()->get_matriz());
                this_node = this_node->get_padre();
                cont++;
            }

            for(u_int16_t a = 0; a < cont; a++){
                matriz_view = matriz_view * pila_matriz_camara.top();
                pila_matriz_camara.pop();
            }
            matriz_view = glm::inverse(matriz_view);
            _shader->setMat4("view", matriz_view);
            glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 100.0f);
            _shader->setMat4("projection", projection);
        }
    }
}
bool TMooseEngine::ventana_abierta(){
    return glfwWindowShouldClose(window);
}
