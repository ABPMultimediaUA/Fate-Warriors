#ifndef SRC_UI_H_
#define SRC_UI_H_
#include <cstdint>
#include <vector>

class Shader;
class Image;

class UI{
    public:
        UI();
        ~UI();
        //funciones de carga de imagenes
        //estas funciones crean una Imagen anyadiendo cada una a su lista correspondiente, ademas cada una de ellas
        //tiene varios constructores que permiten decidir el numero de texturas entre las que puede alternar la imagen
        //esto se usa tanto para marcar botones seleccionados (2 texturas) como para opciones con varios estados como 
        //la resolucion (4 texturas)
        Image* crear_imagen(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_pausa(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        //HUD
        Image* crear_imagenHUD(Shader* shader, const char* ruta, float x, float y, float width, float height);        
        Image* crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagenHUD_llave(Shader* shader, const char* ruta, float x, float y, float width, float height);
        
        //Submenu 1 de configuracion
        Image* crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_config(Shader* shader, const char* ruta, float x, float y, float width, float height);
        
        //Submenu 2 de configuracion
        Image* crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_config_2(Shader* shader, const char* ruta, float x, float y, float width, float height);
        
        //Submenu 3 de configuracion
        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, const char* ruta4, float x, float y, float width, float height);
        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        //menu ganar partida
        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
    
        //menu perder partida
        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        
        //pantalla de carga
        Image* crear_imagen_pantalla_carga(Shader* shader, const char* ruta, float x, float y, float width, float height);

        //funciones de dibujado para los distintos menus y submenus. Estas funciones acceden a cada una de las listas de imagen
        //correspondientes y recorren la lista dibujando cada imagen
        void drawMenu(uint8_t opcion);
        void drawMenuFondo(uint8_t _opcion);
        void drawMenuLogo(uint8_t _opcion);

        void drawAyudaControles();
        void drawFiltroPausa();
        void drawFiltroLose();
        void drawFiltroWin();

        void drawMenuPausa(uint8_t opcion);
        
        void drawMenuConfigSubmenu1(); //music
        void drawMenuConfigSubmenu2(); //gameplay
        void drawMenuConfigSubmenu3(); //graphics

        

        void drawHUD();
        void drawMenuFinWin(uint8_t opcion);
        void drawMenuFinLose(uint8_t opcion);

        
        //ajusta la textura seleccionada en cada uno de los submenus (la opcion sobre la que se encuentra el jugador)
        void setConfigSubmenu1(uint8_t opcion);
        void setConfigSubmenu2(uint8_t opcion);
        void setConfigSubmenu3(uint8_t opcion);

        //ajusta las imagenes de cada opcion para poder reflejar el estado de la opcion seleccionada (off/on, 
        //tamanyo de la barra seleccionada, etc.)
        
        void setFullScreen(bool activar);
        void setVsync(bool activar);

        void set_escala_vida(float escala);
        void set_escala_musica(float escala);
        void set_escala_sfx(float escala);
        void set_escala_voz(float escala);
        void set_escala_sonido_menu(float escala);
        
        void set_eje_x(bool ejeX);
        void set_eje_y(bool ejeY);
        void set_resolution(uint8_t opcion);
        void set_texturas(uint8_t opcion);

        void set_tiene_llave(bool _i_tiene_llave);

        void render_pantalla_carga();
        void render_partida_cargada();

        inline void set_tipo_control(uint8_t _i_tipo_control) { _tipo_control = _i_tipo_control;}

    private:
        //MENU PRINCIPAL
        std::vector<Image*> _lista_imagenes;
        //MENU PAUSA
        std::vector<Image*> _lista_imagenes_pausa;

        //MENU CONFIG
        std::vector<Image*> _lista_imagenes_config;
        //MENU CONFIG 2
        std::vector<Image*> _lista_imagenes_config_2;
        //MENU CONFIG 3
        std::vector<Image*> _lista_imagenes_config_3;

        //HUD
        std::vector<Image*> _lista_imagenes_hud;
        //MENU WIN
        std::vector<Image*> _lista_imagenes_fin_win;
        //MENU LOSE
        std::vector<Image*> _lista_imagenes_fin_lose;
        //PANTALLA CARGA
        std::vector<Image*> _lista_imagenes_carga;

        bool _tiene_llave;
        Image* _img_llave;

        uint8_t _tipo_control;
};

#endif /* SRC_UI_H_ */