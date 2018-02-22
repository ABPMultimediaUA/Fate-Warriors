#ifndef SRC_TCAMARA_H_
#define SRC_TCAMARA_H_
#include "TEntidad.h"

class TCamara : public TEntidad{
    public:
        TCamara();
        ~TCamara();
        void setPerspectiva(float x, float y);
        void setParalela(float x, float y);
        void beginDraw();
        void endDraw();
        void setActiva(bool activa);
        void calculaView();
    private:
        bool es_perspectiva;
        bool _activa;
        float cercano,lejano;
};

#endif /* SRC_TCAMARA_H_ */