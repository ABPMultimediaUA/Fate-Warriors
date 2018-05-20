#include "TMooseEngine.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TLuz.h"
#include "TModelado.h"
#include "TModeladoEscenario.h"
#include "TAnimacion.h"
#include "TGestorRecursos.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ParticleGenerator.h"

#include "UI.h"
#include "Skybox.h"
#include "Mapa.h"


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
    _fullscreen = false;
    _vsync = false;
    glfwSwapInterval(0);
    uint16_t _contadorIDEntidad = 0;
    _n_c_actual=0;
    _n_l_actual=0;
    _gestorRecursos = TGestorRecursos::get_instancia();
    TNodo* nodo     = new TNodo(_contadorIDEntidad,nullptr);//raiz del arbol de escena
    _escena = nodo;
    _shader = new Shader();
    _skybox = new Skybox();

    _mapa = new Mapa(_shader);
    _particulas = new ParticleGenerator(_shader, 20);

    //TAnimacion* anim=new TAnimacion("Anim_ataque_d1_npc2");
   
    SHADOW_WIDTH = 1024;
    SHADOW_HEIGHT = 1024;
    initUI();
}

void TMooseEngine::initUI(){
    _ui = new UI();
    
    //MENU PRINCIPAL
    _ui->crear_imagen(_shader, "Imagenes_Menu/Fondo.png", "Imagenes_Menu/Fondo.png", -1, 1, 2, 2);
    _ui->crear_imagen(_shader, "Imagenes_Menu/Opcion_1.png", "Imagenes_Menu/Opcion_1_Selec.png", -0.26, 0.028, 0.53, 0.215);
    _ui->crear_imagen(_shader, "Imagenes_Menu/Opcion_2.png", "Imagenes_Menu/Opcion_2_Selec.png", -0.26, -0.275, 0.53, 0.215);
    _ui->crear_imagen(_shader, "Imagenes_Menu/Opcion_3.png", "Imagenes_Menu/Opcion_3_Selec.png", -0.26, -0.58, 0.53, 0.215);
    _ui->crear_imagen(_shader, "Imagenes_Menu/Fate_Warriors.png", "Imagenes_Menu/Fate_Warriors.png", -0.288, 0.91, 0.575, 0.548);
    

    //MENU PAUSA
    _ui->crear_imagen_pausa(_shader, "Imagenes_Menu/Opcion_4.png", "Imagenes_Menu/Opcion_4_Selec.png", -0.26, 0.028, 0.53, 0.215);
    _ui->crear_imagen_pausa(_shader, "Imagenes_Menu/Opcion_2.png", "Imagenes_Menu/Opcion_2_Selec.png", -0.26, -0.275, 0.53, 0.215);
    _ui->crear_imagen_pausa(_shader, "Imagenes_Menu/Opcion_3.png", "Imagenes_Menu/Opcion_3_Selec.png", -0.26, -0.58, 0.53, 0.215);
    
    //MENU CONFIG
        // ---------- SUBMENU 1 ----------
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu/Submenu_1.png", "Imagenes_Config/Submenu/Submenu_1_Activo.png", -0.299, 0.162, 0.075, 0.159); //submenu
        
        //textos de opciones
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_Music.png", "Imagenes_Config/Config_Music_Selec.png", -0.1, 0.70, 0.4, 0.3); //musica
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_SFX.png", "Imagenes_Config/Config_SFX_Selec.png", -0.1, 0.50, 0.4, 0.3); //sfx
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_Voices.png", "Imagenes_Config/Config_Voices_Selec.png", -0.1, 0.30, 0.4, 0.3);    //voces
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_Menu.png", "Imagenes_Config/Config_Menu_Selec.png", -0.1, 0.1, 0.4, 0.3);    //menu
        //(4) 
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_X.png", "Imagenes_Config/Config_X_Selec.png", -0.1, -0.1, 0.4, 0.3);    //eje x
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Config_Y.png", "Imagenes_Config/Config_Y_Selec.png", -0.1, -0.3, 0.4, 0.3);    //eje y

        //barra opcion 1 (6)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png", 0.35, 0.60, 0.4, 0.1);     // barra musica
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png",  0.35, 0.60, 0.4, 0.1);     // barra musica
        //barra opcion 2 (8)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png", 0.35, 0.40, 0.4, 0.1);     // barra sfx
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png",  0.35, 0.40, 0.4, 0.1);     // barra sfx
        //barra opcion 3 (10)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png",  0.35, 0.20, 0.4, 0.1);     // barra voces
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png", 0.35, 0.20, 0.4, 0.1);     // barra voces
        //barra opcion 4 (12)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png",  0.35, 0.0, 0.4, 0.1);    // barra menu
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png", 0.35, 0.0, 0.4, 0.1);    // barra menu
        

        // ---------- SUBMENU 2 ----------
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu/Submenu_2.png", "Imagenes_Config/Submenu/Submenu_2_Activo.png", -0.035, 0.162, 0.075, 0.159); //submenu
        
        //boton on/off 1 (14)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/OFF-ON_ON.png", "Imagenes_Config/OFF-ON_OFF.png",  0.4, -0.15, 0.4, 0.2);
        //boton on/off 2 (15)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/OFF-ON_ON.png", "Imagenes_Config/OFF-ON_OFF.png",  0.4, -0.35, 0.4, 0.2);

        _ui->set_eje_x(false);
        _ui->set_eje_y(true);
        

        // ---------- SUBMENU 3 ----------

        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Submenu/Submenu_3.png", "Imagenes_Config/Submenu/Submenu_3_Activo.png", 0.225, 0.162, 0.075, 0.159); //submenu
        
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/negro.png", "Imagenes_Config/fondo.png", 0.1, 0.70, 0.15, 0.15); //vsync
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/negro.png", "Imagenes_Config/fondo.png", 0.1, 0.50, 0.15, 0.15); //res
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/negro.png", "Imagenes_Config/fondo.png", 0.1, 0.30, 0.15, 0.15); //fullscreen
        

    //MENU HUD
    _ui->crear_imagenHUD(_shader, "Imagenes_HUD/HUD_Inferior.png", -0.722, 0.78, 0.326, 0.1);
    _ui->crear_imagenHUD(_shader, "Imagenes_HUD/HUD_Barra_1.png", "Imagenes_HUD/HUD_Barra_2.png", "Imagenes_HUD/HUD_Barra_3.png", -0.722, 0.78, 0.326, 0.1);
    _ui->crear_imagenHUD(_shader, "Imagenes_HUD/HUD_Superior.png", -0.95, 0.85, 0.6, 0.5);
    _ui->crear_imagenHUD(_shader, "Imagenes_HUD/Llave_Silueta.png", 0.75, 0.85, 0.15, 0.15); // Dejar la penultima
    _ui->crear_imagenHUD_llave(_shader, "Imagenes_HUD/Llave.png", 0.75, 0.85, 0.15, 0.15); // Dejar la ultima

    _ui->set_escala_musica(5);
    _ui->set_escala_sfx(5);
    _ui->set_escala_voz(5);
    _ui->set_escala_sonido_menu(5);
    
    //MENU WIN
    _ui->crear_imagen_fin_win(_shader, "Imagenes_Menu/Opcion_1.png", -0.3, 0.4, 0.6, 0.5);
    _ui->crear_imagen_fin_win(_shader, "Imagenes_Menu/Opcion_5.png", "Imagenes_Menu/Opcion_5_Selec.png", -0.26, 0.028, 0.53, 0.215);
    _ui->crear_imagen_fin_win(_shader, "Imagenes_Menu/Opcion_3.png", "Imagenes_Menu/Opcion_3_Selec.png", -0.26, -0.275, 0.53, 0.215);

    //MENU LOSE
    _ui->crear_imagen_fin_lose(_shader, "Imagenes_Menu/Opcion_1.png", -0.3, 0.4, 0.6, 0.5);
    _ui->crear_imagen_fin_lose(_shader, "Imagenes_Menu/Opcion_5.png", "Imagenes_Menu/Opcion_5_Selec.png", -0.26, 0.028, 0.53, 0.215);
    _ui->crear_imagen_fin_lose(_shader, "Imagenes_Menu/Opcion_3.png", "Imagenes_Menu/Opcion_3_Selec.png", -0.26, -0.275, 0.53, 0.215);
    

    // PANTALLA CARGA
    _ui->crear_imagen_pantalla_carga(_shader, "Imagenes_Carga/Loading.png", -0.6, 0.6, 1.2, 0.22);
    _ui->crear_imagen_pantalla_carga(_shader, "Imagenes_Carga/Ready.png", -0.6, 0.6, 1.2, 0.22);
    //ANYADIR IMAGEN DE MANDO CON CONTROLES E IMAGEN DE 'PULSA A PARA CONTINUAR'
}

void TMooseEngine::toggleFullscreen(){
    _fullscreen = !_fullscreen;
    
    if(_fullscreen){
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, _width, _height, 60);
    }

    else{
        glfwSetWindowMonitor(window, NULL, 0, 0, _width, _height, 60);    
    }
}

void TMooseEngine::toggleVSync(){
    _vsync != _vsync;
    
    if(_vsync){
        glfwSwapInterval(1);
    }
    else{
        glfwSwapInterval(0);
    }
}

//reinicia la resolucion a pantalla completa a la resolucion del monitor
//se utiliza para evitar errores graficos al cerrar el juego con resoluciones distintas a la nativa en fullscreen
void TMooseEngine::reset_resolution(){
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    int window_width = mode->width;
    int window_height = mode->height;

    glfwSetWindowMonitor(window, NULL, 0, 0, window_width, window_height, 60);

}

void TMooseEngine::PreparacionSombras(){
    glGenFramebuffers(1, &depthMapFBO);  
   //generacion de la textura del mapeado de sombras
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    //bind del mapeado de sombras
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

void TMooseEngine::ConfigurarSombrasMapeado(){
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.5f, 100.0f);  
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),glm::vec3( 0.0f, 0.0f,  0.0f),glm::vec3( 0.0f, 1.0f,  0.0f));  
}

void TMooseEngine::ConfigurarSombrasProyectadas(){
      
}

TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    _mapping_luces.clear();
    _mapping_camaras.clear();
    delete _shader;
    delete _skybox;
    delete _particulas;
    delete _mapa;
    _contadorIDEntidad=0;
    glfwTerminate();
}

void micallback(GLFWwindow* oglwindow, double _i_xpos, double _i_ypos){
    TMooseEngine::get_instancia()->mouse_callback(oglwindow, _i_xpos, _i_ypos);
}

void TMooseEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (_firstMouse)
    {
        _lastX = xpos;
        _lastY = ypos;
        _firstMouse = false;
    }

    float xoffset = xpos - _lastX;
    float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

    _lastX = xpos;
    _lastY = ypos;
    
    setMouseOffsetX(xoffset);
    setMouseOffsetY(yoffset);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    TMooseEngine::get_instancia()->guarda_tamanyo_viewport(width,height);
    glViewport(0, 0, width, height);

}

void TMooseEngine::guarda_tamanyo_viewport(int width,int height){
 _width = width;
 _height = height;
}

void TMooseEngine::init_opengl(uint16_t width, uint16_t height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Fate Warriors", NULL, NULL);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, micallback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(0);

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
    //culling
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,width,height);
    guarda_tamanyo_viewport(width,height);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    glFrontFace(GL_CCW);

    //const char * extension= "GLX_EXT_swap_control";
    //bool supported = glfwExtensionSupported(extension);
    
    
}

float TMooseEngine::getMouseOffsetX(){
    return _offsetX;
}

float TMooseEngine::getMouseOffsetY(){
    return _offsetY;
}

void TMooseEngine::setMouseOffsetX(float offset){
    _offsetX = offset;
}

void TMooseEngine::setMouseOffsetY(float offset){
    _offsetY = offset;
}

void TMooseEngine::borrarNodo(uint16_t nodo){
    TNodo* aux=_escena->encontrarNodo(nodo);
    
    if(aux==nullptr){
        std::cout<<"ERROR ARBOL ESCENA: nodo no encontrado"<<"\n";
    }
    if(aux->get_padre()->get_hijos_size()>1){
        aux->borrar_nodo();
    }else{
        aux=aux->get_padre();
    }
}


TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){
    ++_contadorIDEntidad;     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    nodo->set_entidad(ent);
    padre->agrega_hijo(nodo);
    return nodo;
}

TNodo* TMooseEngine::crearNodoCamara(TNodo *padre, TEntidad *ent){
    ++_contadorIDEntidad;     
    TNodo* aux=crearNodo(padre,ent);
    _mapping_camaras.push_back(new Mapeado({true,aux}));
    ++_n_c_actual;
    return aux;
}
TNodo* TMooseEngine::crearNodoLuz(TNodo *padre, TEntidad *ent){
    ++_contadorIDEntidad;     
    TNodo* aux=crearNodo(padre,ent);
    _mapping_luces.push_back(new Mapeado({true,aux}));
    ++_n_l_actual;
    return aux;
}

Image_Map* TMooseEngine::anyadir_elemento_al_mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo){
    return _mapa->anyadir_elemento_al_mapa(x,  y,  ancho,  alto,  tipo);
}

void TMooseEngine::eliminar_elemento_del_mapa(Image_Map* elemento_a_eliminar){
    _mapa->eliminar_elemento_mapa(elemento_a_eliminar);
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
    return malla;
}
TModeladoEscenario* TMooseEngine::crearModeladoEscenario(const char* _i_path){
    TModeladoEscenario* malla = new TModeladoEscenario(_i_path);
    return malla;
}
TAnimacion* TMooseEngine::crearAnimacion(const char* _i_path){ 
    TAnimacion* animacion = new TAnimacion(_i_path); 
    _animaciones.push_back(animacion);
    return animacion; 
} 

void TMooseEngine::clear(){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void TMooseEngine::draw(){
    _skybox->draw(_shader, _shader->getView(),  _shader->getProjection());
    _shader->use(Default);
    drawCamaras();
    drawLuces();
    _escena->draw(_shader);
    _skybox->draw(_shader, _shader->getView(),  _shader->getProjection());

    _shader->use(sombras_proyectadas);
    _escena->draw(_shader);
    _particulas->Draw();

}



void TMooseEngine::render_estado_Partida(){
    clear();
    draw();
    renderUIHUD();
   // glViewport(_width*0.7, 0, 600, 600);
    glViewport(800, 0, 420, 560);
   
    _mapa->Draw();
    glViewport(0, 0, _width, _height);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::renderUIMenu(uint16_t opcion, uint16_t opcion2, bool config_abierta){
    clear();
    glDisable(GL_CULL_FACE);
    
    _ui->drawMenuFondo(opcion);
    if(config_abierta) {
        renderUIMenuConfig(opcion2);
    }
    else {
        _ui->drawMenu(opcion);
    }
    _ui->drawMenuLogo(opcion);

    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::renderUIMenuPausa(uint16_t opcion, uint16_t opcion2, bool config_abierta){
    clear();
    draw();
    glDisable(GL_CULL_FACE);
    _ui->drawMenuPausa(opcion);
    if(config_abierta){
        renderUIMenuConfig(opcion2);
    }
    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::renderUIMenuConfig(uint16_t opcion){
    //glDisable(GL_CULL_FACE);
    _ui->drawMenuConfig(opcion);
    //glEnable(GL_CULL_FACE);
    //glfwSwapBuffers(window);
}

void TMooseEngine::renderUIMenuWin(uint16_t opcion){
    clear();
    draw();
    glDisable(GL_CULL_FACE);
    _ui->drawMenuFinWin(opcion);
    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
}

void TMooseEngine::renderUIMenuLose(uint16_t opcion){
    clear();
    draw();
    glDisable(GL_CULL_FACE);
    _ui->drawMenuFinLose(opcion);
    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
}

void TMooseEngine::renderUIHUD(){
    clear();
    draw();
    glDisable(GL_CULL_FACE);
    _ui->drawHUD();
    glEnable(GL_CULL_FACE);
    //glfwSwapBuffers(window);
}

void TMooseEngine::render_pantalla_carga(){
    clear();
    glDisable(GL_CULL_FACE);
    
    _ui->render_pantalla_carga();

    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::render_partida_cargada(){
    clear();
    glDisable(GL_CULL_FACE);
    
    _ui->render_partida_cargada();

    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::apagar(){
    if(_fullscreen){
        reset_resolution();
    }
   glfwSetWindowShouldClose(window, true);
}


void TMooseEngine::drawLuces(){
    u_int16_t cont = 0;
    glm::vec3 position;
    std::stack<glm::mat4> pila_matriz_luz;
    glm::vec3 luz_aux[4];
    matriz_luz=glm::mat4(1.0f);
    TNodo* aux;
    for(uint16_t i = 0; i < _mapping_luces.size(); i++){
        if(_mapping_luces[i]->activa){//eleccion de las luces activas
            TNodo* this_node = _mapping_luces[i]->nodo;
            //se guarda en un array para pasarlo al shader
            luz_aux[0]=static_cast<TLuz*>(this_node->get_entidad())->get_difusa();
            luz_aux[1]=static_cast<TLuz*>(this_node->get_entidad())->get_especular();
            luz_aux[2]=static_cast<TLuz*>(this_node->get_entidad())->get_ambiente();
            while(this_node->get_padre()!=nullptr){//se guardan los padres en una pila
                this_node = this_node->get_padre();
                if(this_node->get_entidad()!=nullptr){
                    pila_matriz_luz.push(static_cast<TTransform*> (this_node->get_entidad())->get_t_matriz());
                    cont++;
                    
                }
            }

            for(u_int16_t a = 0; a < cont; a++){//se recorre la pila para coger la posicion de la luz
               matriz_luz = matriz_luz * pila_matriz_luz.top();
               if(a==cont-1){
                   position = glm::vec3(pila_matriz_luz.top()[3][0],
                                                  pila_matriz_luz.top()[3][1],
                                                  pila_matriz_luz.top()[3][2]);

                    luz_aux[3]=position;
                    glm::mat4 mat(20,0,0,0,
                                  0,0,0,0,
                                  0,0,20,0,
                                  0,-1,0,20);
                    _shader->setLuz(luz_aux,i);//paso de la luz
                    _shader->use(sombras_proyectadas);
                    _shader->setMat4("luz_proyeccion",mat);
                    _shader->use(Default);
               }
               pila_matriz_luz.pop();
            } 
            cont=0;
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
            matriz_view = static_cast<TCamara*>(this_node->get_entidad())->calculaView();
            _shader->setView(matriz_view); //la pasamos al shader
            glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 10000.0f);
            projection = glm::scale(projection, glm::vec3(-1.0f, 1.0f, 1.0f));
            _shader->setProjection(projection);

        }
    }
}

bool TMooseEngine::ventana_abierta(){
    return glfwWindowShouldClose(window);
}

ParticleGenerator* TMooseEngine::get_gestor_particulas(){
    return _particulas;
}

void TMooseEngine::resize_window(int _i_width, int _i_height) {
    glfwSetWindowSize(window, _i_width, _i_height);
}