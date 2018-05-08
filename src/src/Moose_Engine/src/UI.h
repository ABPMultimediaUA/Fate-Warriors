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



        void drawMenu(uint16_t opcion);
        void drawMenuPausa(uint16_t opcion);
        void drawHUD();

        void set_escala_vida(float escala);
        

    private:
        
        //MENU PRINCIPAL
        std::vector<Image*> _lista_imagenes;
        //MENU PAUSA
        std::vector<Image*> _lista_imagenes_pausa;
        //HUD
        std::vector<Image*> _lista_imagenes_hud;
};

#endif /* SRC_UI_H_ */