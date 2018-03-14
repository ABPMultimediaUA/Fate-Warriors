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

TMooseEngine* TMooseEngine::_instancia = 0;

struct Mapeado{//declaracion de los parametros
    bool activa;
    TNodo* nodo;
};

TMooseEngine* TMooseEngine::get_instancia(){
    if(_instancia == 0){
        _instancia = new TMooseEngine();
    }
    return _instancia;
}

TMooseEngine::TMooseEngine(){
    init_opengl(1280, 720);
    uint16_t _contadorIDEntidad = 0;
    _n_c_actual=0;
    _n_l_actual=0;
    _gestorRecursos = TGestorRecursos::get_instancia();
    TNodo* nodo     = new TNodo(_contadorIDEntidad,nullptr);
    _escena = nodo;
    _shader = new Shader("src/Moose_Engine/Shaders/vertex_prueba.glsl", "src/Moose_Engine/Shaders/fragment_prueba.glsl");
}

TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    _mapping_luces.clear();
    _mapping_camaras.clear();
    delete _shader;
    _contadorIDEntidad=0;
    glfwTerminate();
}

void TMooseEngine::init_opengl(uint16_t width, uint16_t height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "MooseEngine", NULL, NULL);
   

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
    glViewport(0,0,width,height);
}

TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    nodo->set_entidad(ent);
    padre->agrega_hijo(nodo);
    ++_contadorIDEntidad;
    return nodo;
}

TNodo* TMooseEngine::crearNodoCamara(TNodo *padre, TEntidad *ent){
    TNodo* aux=crearNodo(padre,ent);
    _mapping_camaras.push_back(new Mapeado({true,aux}));
    ++_n_c_actual;
    return aux;
}
TNodo* TMooseEngine::crearNodoLuz(TNodo *padre, TEntidad *ent){
    TNodo* aux=crearNodo(padre,ent);
    _mapping_luces.push_back(new Mapeado({true,aux}));
    ++_n_l_actual;
    return aux;
}

TTransform* TMooseEngine::crearTransform(){
    TTransform* transform = new TTransform();
    return transform;
}

TCamara* TMooseEngine::crearCamara(bool activa){
    TCamara* camara = new TCamara();
    camara->setActiva(activa);
    return camara;
}

TLuz* TMooseEngine::crearLuz(glm::vec3 ambiente, glm::vec3 especular, glm::vec3 difusa){
    TLuz* luz = new TLuz(ambiente,especular,difusa);
    return luz;
}

TModelado* TMooseEngine::crearModelado(const char* _i_path){
    TModelado* malla = new TModelado(_i_path);
    //_gestorRecursos->getRecursoModelo(fichero);
    return malla;
}

void TMooseEngine::clear(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }else{
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
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
    matriz_luz=glm::mat4(1.0f);
    TNodo* aux;
    for(uint16_t i = 0; i < _mapping_luces.size(); i++){
        if(_mapping_luces[i]->activa){
            TNodo* this_node = _mapping_luces[i]->nodo;
            
            while(this_node->get_padre()!=nullptr){
                aux=this_node;
                this_node = this_node->get_padre();
                if(this_node->get_entidad()!=nullptr){
                    pila_matriz_luz.push(static_cast<TTransform*> (this_node->get_entidad())->get_t_matriz());
                    cont++;
                    //std::cout << "drawentidad "<<aux->get_entidad_id()<<"\n";
                    //std::cout<<static_cast<TLuz*>(aux->get_entidad())->get_especular().y<<std::endl;
                    _shader->setvec3("Light.Diffuse",static_cast<TLuz*>(aux->get_entidad())->get_difusa());
                    _shader->setvec3("Light.Specular",static_cast<TLuz*>(aux->get_entidad())->get_especular());
                    _shader->setvec3("Light.Ambient",static_cast<TLuz*>(aux->get_entidad())->get_ambiente());
                }
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
    matriz_view=glm::mat4(1.0f); //inicializar la matriz view
    for(uint16_t i = 0; i < _mapping_camaras.size(); i++){ 
        if(_mapping_camaras[i]->activa){ //recorremos el mapeado de camaras buscando la que este activa
            TNodo* this_node = _mapping_camaras[i]->nodo; //obtenemos su nodo
            while(this_node->get_padre()!=nullptr){ //subimos hacia arriba en el arbol hasta la raiz
                this_node = this_node->get_padre();
                if(this_node->get_entidad()!=nullptr){ //para cada nodo salvo el raiz:
                                                       //accedemos a la matriz de su transformacion y la apilamos para calcular la matriz view
                    pila_matriz_camara.push(static_cast<TTransform*> (this_node->get_entidad())->get_t_matriz());
                    cont++;//contamos el numero de veces que hemos apilado una matriz
                }
                
            }

            for(u_int16_t a = 0; a < cont; a++){ //por cada matriz apilada... 
                matriz_view = matriz_view * pila_matriz_camara.top(); //construimos la matriz view multiplicando en orden inverso
                pila_matriz_camara.pop();
            }
            //std::cout<<"view: "<<glm::to_string(matriz_view)<<"\n";
            matriz_view = glm::inverse(matriz_view); //invertimos la matriz para obtener la matriz view final
            _shader->setView(matriz_view); //la pasamos al shader
            glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 100.0f);
            _shader->setProjection(projection);
        }
    }
}
bool TMooseEngine::ventana_abierta(){
    return glfwWindowShouldClose(window);
}
