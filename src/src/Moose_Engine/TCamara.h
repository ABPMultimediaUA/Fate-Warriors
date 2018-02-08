#ifndef SRC_TCAMARA_H_
#define SRC_TCAMARA_H_
#include "TEntidad.h"

class TCamara : TEntidad{
    public:
        TCamara();
        ~TCamara();
        void setPerspectiva(float x, float y);
        void setParalela(float x, float y);
    private:
        bool es_perspectiva;
        float cercano,lejano;
};

#endif /* SRC_TCAMARA_H_ */