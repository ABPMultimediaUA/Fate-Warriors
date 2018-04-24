#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

UI* UI::_instancia = 0;

UI* UI::ui_instancia(uint16_t ancho_ventana, uint16_t alto_ventana){
	if(_instancia == 0)
		_instancia= new UI(ancho_ventana, alto_ventana);
	return _instancia;
}
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}
/*Funciones para guardar los datos
 * */
struct Tresolution2func{//declaracion de los parametros
	int _n_res;
	void (UI::*pmet)();
};

Tresolution2func UI_mapping[] = {//definicion de los parametros
		{1920, &UI::cargar_res_1920}
       /* {1600, &UI::cargar_res_1600},
        {1366, &UI::cargar_res_1366},
        {1280, &UI::cargar_res_1280},
        {1024, &UI::cargar_res_1024},
        {800, &UI::cargar_res_800},
        {640, &UI::cargar_res_640},
		{0, &UI::cargar_res_default}*/
};
UI::UI(uint16_t ancho_ventana, uint16_t alto_ventana){
    _cierratePuto = false;
    
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
    //std::cout<<"algo nbo va bien"<<std::endl;
    }
    _ancho_ventana = ancho_ventana;
    _alto_ventana = alto_ventana;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(ancho_ventana, alto_ventana, "GUI TEST", NULL, NULL);
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1); // Enable vsync
    

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(_window, true);
    // Setup style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    _show_demo_window = true;
    _clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    
    ImGuiIO& io = ImGui::GetIO();
    ImFont* pFont = io.Fonts->AddFontFromFileTTF("Goalthink-Regular.ttf", 30.0f);
    //io.FontDefault = pFont;
    //unsigned char* pixels;
    //int width, height;
    //io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);


    Tresolution2func* _next=UI_mapping;
	//std::cout<<_iteracion<<std::endl;
	while (_next->_n_res){
		if(ancho_ventana==_next->_n_res){
			(this->*_next->pmet)();
            break;
		}
		++_next;
	}
    if (! _next->_n_res){
        (this->*_next->pmet)();
    }
}

UI::~UI(){
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
}

void UI::cargar_res_1920(){
    _boton_ancho=300;
    _boton_alto=100;
    _posicion_menu_std_X = (_ancho_ventana/2)-(_boton_ancho/2);
    _posicion_menu_std_Y = (_alto_ventana/2)-(_boton_alto*3/2)-(30*3/2);
}

void UI::update(){
    //if(glfwWindowShouldClose(_window)){
    //    _cierratePuto = true;
    //}
//
    //glfwPollEvents();
    ImGui_ImplGlfwGL3_NewFrame();
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    
   
    ImGuiStyle& style = ImGui::GetStyle();

    
    //style.WindowRounding = 5.3f;
    //style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;
    //style.ColumnsMinSpacing = 200.0f;
    style.ItemSpacing = ImVec2(0, 20);
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    //style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
   // style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 0.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.85f, 0.0f, 0.00f, 1.f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.85f, 0.3f, 0.3f, 1.f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.00f, 0.00f, 1.f);
    
   // ImFont* fuente = ImGui::GetIO().Fonts->AddFontFromFileTTF("Goalthink-Regular.ttf", 14);
    
    //ImGui::GetIO().Fonts->Clear();
    //fuente = ImGui::GetIO().Fonts->AddFontFromFileTTF("Goalthink-Regular.ttf", 14);


        
    {
        ImGui::SetNextWindowPos(ImVec2(_posicion_menu_std_X,_posicion_menu_std_Y));
        ImGui::Begin("Menu principal",0,ImGuiWindowFlags_NoTitleBar|
                                        ImGuiWindowFlags_NoResize|
                                        ImGuiWindowFlags_AlwaysAutoResize|
                                        ImGuiWindowFlags_NoMove);

        ImGui::Button("Jugar", ImVec2(_boton_ancho,_boton_alto));
        ImGui::Button("Ajustes", ImVec2(_boton_ancho,_boton_alto));
        ImGui::Button("Salir", ImVec2(_boton_ancho,_boton_alto));
        
        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        ImGui::End();
    }
    
    // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
    //if (_show_demo_window)
    //{
    //    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
    //    ImGui::ShowDemoWindow(&_show_demo_window);
    //}
    
}

void UI::render(){
    // Rendering
    //int display_w, display_h;
    //glfwGetFramebufferSize(_window, &display_w, &display_h);
    //glViewport(0, 0, display_w, display_h);
    //glClearColor(_clear_color.x, _clear_color.y, _clear_color.z, _clear_color.w);
    //glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    //glfwSwapBuffers(_window);
}

bool UI::get_cerrar(){
    return _cierratePuto;
}