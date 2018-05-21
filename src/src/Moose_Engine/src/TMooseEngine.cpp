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
    _resolution = 1;
    _texture_quality = 0;
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
    
    // -------------------------- INICIO OPCIONES --------------------------
        // ---------- SUBMENU 1 ----------  (0)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu/Submenu_1.png", "Imagenes_Config/Submenu/Submenu_1_Selec.png", "Imagenes_Config/Submenu/Submenu_1_Activo.png", -0.299, 0.162, 0.075, 0.159);

        // MUSIC    (1)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu_1/Option_Music.png", "Imagenes_Config/Submenu_1/Option_Music_Selec.png", -0.47, -0.16, 0.431, 0.12);
        // SFX      (2)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu_1/Option_SFX.png", "Imagenes_Config/Submenu_1/Option_SFX_Selec.png", -0.47, -0.362, 0.431, 0.12);
        // VOICES   (3)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu_1/Option_Voices.png", "Imagenes_Config/Submenu_1/Option_Voices_Selec.png", -0.47, -0.565, 0.431, 0.12);
        // MENU     (4)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Submenu_1/Option_Menu.png", "Imagenes_Config/Submenu_1/Option_Menu_Selec.png", -0.47, -0.767, 0.431, 0.12);

        
        // Barra Music  (5, 6)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png", 0.03, -0.153, 0.416, 0.13); 
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png",  0.03, -0.153, 0.416, 0.13); 
        // Barra SFX    (7, 8)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png", 0.03, -0.355, 0.416, 0.13); 
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png",  0.03, -0.355, 0.416, 0.13); 
        // Barra Voice  (9, 10)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png",  0.03, -0.558, 0.416, 0.13); 
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png", 0.03, -0.558, 0.416, 0.13); 
        // Barra Menu   (11,12)
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Fondo.png",  0.03, -0.76, 0.416, 0.13); 
        _ui->crear_imagen_config(_shader, "Imagenes_Config/Barra_Frente.png", 0.03, -0.76, 0.416, 0.13); 
        


        // ---------- SUBMENU 2 ----------  (0)
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Submenu/Submenu_2.png", "Imagenes_Config/Submenu/Submenu_2_Selec.png", "Imagenes_Config/Submenu/Submenu_2_Activo.png", -0.035, 0.162, 0.075, 0.159);
        
        // EJE X    (1)
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Submenu_2/Option_X.png", "Imagenes_Config/Submenu_2/Option_X_Selec.png", -0.47, -0.16, 0.431, 0.12);
        // EJE Y    (2)
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Submenu_2/Option_Y.png", "Imagenes_Config/Submenu_2/Option_Y_Selec.png", -0.47, -0.362, 0.431, 0.12);

        // OFF - ON     (3)
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Opcion_ON.png", "Imagenes_Config/Opcion_OFF.png", 0.045, -0.169, 0.305, 0.101);
        // OFF - ON     (4)
        _ui->crear_imagen_config_2(_shader, "Imagenes_Config/Opcion_ON.png", "Imagenes_Config/Opcion_OFF.png", 0.045, -0.368, 0.305, 0.101);

        _ui->set_eje_x(false);
        _ui->set_eje_y(true);
        


        // ---------- SUBMENU 3 ----------  (0)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Submenu/Submenu_3.png", "Imagenes_Config/Submenu/Submenu_3_Selec.png", "Imagenes_Config/Submenu/Submenu_3_Activo.png", 0.225, 0.162, 0.075, 0.159);
        
        // RESOLUTION   (1)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Submenu_3/Option_Resolution.png", "Imagenes_Config/Submenu_3/Option_Resolution_Selec.png", -0.47, -0.16, 0.431, 0.12);
        // V-SYNC       (2)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Submenu_3/Option_VSync.png", "Imagenes_Config/Submenu_3/Option_VSync_Selec.png", -0.47, -0.362, 0.431, 0.12);
        // FULLSCREEN   (3)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Submenu_3/Option_Fullscreen.png", "Imagenes_Config/Submenu_3/Option_Fullscreen_Selec.png", -0.47, -0.565, 0.431, 0.12);
        // TEXTURES     (4)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Submenu_3/Option_Textures.png", "Imagenes_Config/Submenu_3/Option_Textures_Selec.png", -0.47, -0.767, 0.431, 0.12);
        

        // RESOLUTIONS  (5)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Resoluciones/640_480.png", "Imagenes_Config/Resoluciones/1024_768.png", "Imagenes_Config/Resoluciones/1280_720.png", "Imagenes_Config/Resoluciones/1920_1080.png", 0.048, -0.15, 0.477, 0.141);
        // OFF - ON     (6)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Opcion_OFF.png", "Imagenes_Config/Opcion_ON.png", 0.139, -0.368, 0.305, 0.101);
        // OFF - ON     (7)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Opcion_OFF.png", "Imagenes_Config/Opcion_ON.png", 0.139, -0.575, 0.305, 0.101);
        // TEXTURES     (8)
        _ui->crear_imagen_config_3(_shader, "Imagenes_Config/Texturas/Low.png", "Imagenes_Config/Texturas/Medium.png", "Imagenes_Config/Texturas/High.png", 0.048, -0.758, 0.477, 0.141);


    // -------------------------- FIN OPCIONES --------------------------

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
        _ui->setFullScreen(true);
    }

    else{
        glfwSetWindowMonitor(window, NULL, 0, 0, _width, _height, 60);    
        _ui->setFullScreen(false);
    }
}

void TMooseEngine::toggleVSync(){
    _vsync = !_vsync;
    
    if(_vsync){
        glfwSwapInterval(1);
        _ui->setVsync(true);
    }
    else{
        glfwSwapInterval(0);
        _ui->setVsync(false);
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
    float _escala = width / height;
    float _escala_buena = 16.0/9.0;
    int _i_width = width; 
    int _i_height = height; 
    int _i_offset_viewport_X = 0;
    int _i_offset_viewport_Y = 0;

    if(_escala > _escala_buena) {
        _i_width = height * _escala_buena;
        _i_offset_viewport_X = (width-_i_width) / 2;
    }
    else if(_escala < _escala_buena) {
        _i_height = width / _escala_buena;
        _i_offset_viewport_Y = (height-_i_height) / 2;
    }

    TMooseEngine::get_instancia()->guarda_tamanyo_viewport(_i_offset_viewport_X, _i_offset_viewport_Y, _i_width, _i_height);
    glViewport(_i_offset_viewport_X, _i_offset_viewport_Y, _i_width, _i_height);
}

void TMooseEngine::guarda_tamanyo_viewport(int _i_offset_viewport_X, int _i_offset_viewport_Y, int width,int height){
    _offset_viewport_X = _i_offset_viewport_X;
    _offset_viewport_Y = _i_offset_viewport_Y;
    _width = width;
    _height = height;

    cambiar_posicion_y_tamanyo_minimapa(0.8,0,1.2);

/*
    glm::vec2 vertexPosition_homoneneousspace = glm::vec2(0.8,0); 
    vertexPosition_homoneneousspace *= glm::vec2(_width,_height);

    glm::vec2 scale_homoneneousspace = glm::vec2(0.42/1.2,0.56/1.2);
    scale_homoneneousspace *= glm::vec2(_width,_width);

    _position_x_minimapa = vertexPosition_homoneneousspace.x;
    _position_y_minimapa = vertexPosition_homoneneousspace.y;

    _width_minimapa = scale_homoneneousspace.x;
    _height_minimapa = scale_homoneneousspace.y;
*/

}

void TMooseEngine::cambiar_posicion_y_tamanyo_minimapa(float x, float y, float scala){
    glm::vec2 vertexPosition_homoneneousspace = glm::vec2(x,y); 
    vertexPosition_homoneneousspace *= glm::vec2(_width,_height);

    glm::vec2 scale_homoneneousspace = glm::vec2(0.42/scala,0.56/scala);
    scale_homoneneousspace *= glm::vec2(_width,_width);

    _position_x_minimapa = vertexPosition_homoneneousspace.x;
    _position_y_minimapa = vertexPosition_homoneneousspace.y;

    _width_minimapa = scale_homoneneousspace.x;
    _height_minimapa = scale_homoneneousspace.y;
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

    float _escala = width / height;
    float _escala_buena = 16.0/9.0;
    
    _width = width;
    _height = _height;
    _offset_viewport_X = 0;
    _offset_viewport_Y = 0;

    if(_escala > _escala_buena) {
        _width = height * _escala_buena;
        _offset_viewport_X = (width-_width) / 2;
    }
    else if(_escala < _escala_buena) {
        _height = width / _escala_buena;
        _offset_viewport_Y = (height-_height) / 2;
    }
    
    glEnable(GL_DEPTH_TEST);
    glViewport(_offset_viewport_X, _offset_viewport_Y, _width, _height);
    guarda_tamanyo_viewport(_offset_viewport_X, _offset_viewport_Y, _width, _height);
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    glViewport(_position_x_minimapa+_offset_viewport_X, _position_y_minimapa+_offset_viewport_Y, _width_minimapa, _height_minimapa);
   

    _mapa->Draw();
    glViewport(_offset_viewport_X, _offset_viewport_Y, _width, _height);

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

    if(config_abierta){
        renderUIMenuConfig(opcion2);
    }
    else {
        _ui->drawMenuPausa(opcion);
    }
    
    glEnable(GL_CULL_FACE);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TMooseEngine::renderUIMenuConfig(uint16_t opcion){
    //glDisable(GL_CULL_FACE);
    if(opcion < 5)
		_ui->drawMenuConfigSubmenu1();
	else if(opcion < 8)
		_ui->drawMenuConfigSubmenu2();
	else
		_ui->drawMenuConfigSubmenu3();

    //_ui->drawMenuConfig(opcion);
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
            glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)_width / (float)_height, 0.1f, 10000.0f);
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

bool TMooseEngine::get_fullscreen(){
    return _fullscreen;
}

bool TMooseEngine::get_vsync(){
    return _vsync;
}

uint8_t TMooseEngine::get_resolution(){
    return _resolution;
}

uint8_t TMooseEngine::get_calidad_texturas(){
    return _texture_quality;
}

void TMooseEngine::set_resolution(uint8_t res){
    _resolution = res;
}

void TMooseEngine::set_calidad_texturas(uint8_t calidad){
    _texture_quality = calidad;
}