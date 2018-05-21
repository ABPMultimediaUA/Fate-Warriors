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
        Image* crear_imagen(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_pausa(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        Image* crear_imagenHUD(Shader* shader, const char* ruta, float x, float y, float width, float height);        
        Image* crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagenHUD_llave(Shader* shader, const char* ruta, float x, float y, float width, float height);

        Image* crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_config(Shader* shader, const char* ruta, float x, float y, float width, float height);

        Image* crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_config_2(Shader* shader, const char* ruta, float x, float y, float width, float height);

        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, const char* ruta4, float x, float y, float width, float height);
        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height);
        Image* crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        Image* crear_imagen_pantalla_carga(Shader* shader, const char* ruta, float x, float y, float width, float height);

        void drawMenu(uint8_t opcion);
        void drawMenuFondo(uint8_t _opcion);
        void drawMenuLogo(uint8_t _opcion);
        void drawMenuPausa(uint8_t opcion);
        
        void drawMenuConfigSubmenu1(); //music
        void drawMenuConfigSubmenu2(); //gameplay
        void drawMenuConfigSubmenu3(); //graphics
        void setConfigSubmenu1(uint8_t opcion);
        void setConfigSubmenu2(uint8_t opcion);
        void setConfigSubmenu3(uint8_t opcion);

        void setFullScreen(bool activar);
        void setVsync(bool activar);

        void drawHUD();
        void drawMenuFinWin(uint8_t opcion);
        void drawMenuFinLose(uint8_t opcion);

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

};

#endif /* SRC_UI_H_ */