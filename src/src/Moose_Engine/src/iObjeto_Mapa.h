#ifndef SRC_IOBJETO_MAPA_H_
#define SRC_IOBJETO_MAPA_H_

#include "Enum_Texturas.h"
class Image_Map;

class iObjeto_Mapa{
    public:
        iObjeto_Mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo);
        virtual ~iObjeto_Mapa();
        void setTextureposition(float x, float y, float rotacion = 0);

    private:
        Image_Map* _imagen_mapa; //nodo interno del ME
};

#endif