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

        Image* crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);
        Image* crear_imagen_config(Shader* shader, const char* ruta, float x, float y, float width, float height);

        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_win(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);

        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, float x, float y, float width, float height);
        Image* crear_imagen_fin_lose(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height);


        void drawMenu(uint16_t opcion);
        void drawMenuPausa(uint16_t opcion);
        void drawMenuConfig(uint16_t opcion);
        void drawHUD();
        void drawMenuFinWin(uint16_t opcion);
        void drawMenuFinLose(uint16_t opcion);

        void set_escala_vida(float escala);

        void set_escala_musica(float escala);
        void set_escala_sfx(float escala);
        void set_escala_voz(float escala);
        void set_escala_sonido_menu(float escala);
        
        void set_eje_x(bool ejeX);
        void set_eje_y(bool ejeY);

        void set_tiene_llave(bool _i_tiene_llave);

    private:
        //MENU PRINCIPAL
        std::vector<Image*> _lista_imagenes;
        //MENU PAUSA
        std::vector<Image*> _lista_imagenes_pausa;
        //MENU CONFIG
        std::vector<Image*> _lista_imagenes_config;
        //HUD
        std::vector<Image*> _lista_imagenes_hud;
        //MENU WIN
        std::vector<Image*> _lista_imagenes_fin_win;
        //MENU LOSE
        std::vector<Image*> _lista_imagenes_fin_lose;

        bool _tiene_llave;
        Image* _img_llave;

};

#endif /* SRC_UI_H_ */