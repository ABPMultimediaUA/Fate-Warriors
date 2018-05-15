#ifndef SRC_IOBJETO_MAPA_H_
#define SRC_IOBJETO_MAPA_H_

class Image_Map;

class iObjeto_Mapa{
    public:
        iObjeto_Mapa();
        virtual ~iObjeto_Mapa();
        void setTextureposition(float x, float y);

    private:
        Image_Map* _imagen_mapa; //nodo interno del ME
};

#endif