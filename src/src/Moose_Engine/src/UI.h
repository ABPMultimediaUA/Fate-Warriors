#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <vector>

class Shader;
class Image;

class UI{
    public:
        UI();
        ~UI();
        Image* crear_imagen(Shader* shader, const char* ruta, float x, float y, float width, float height);
        
        void drawMenu();
        void drawUI();

    private:
        std::vector<Image*> _lista_imagenes;
};

#endif /* SRC_UI_H_ */