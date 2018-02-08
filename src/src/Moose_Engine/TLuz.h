#ifndef SRC_TLUZ_H_
#define SRC_TLUZ_H_
#include "TEntidad.h"
class TColor;

class TLuz : TEntidad{
    public:
        TLuz();
        ~TLuz();
        inline void seIntensidad(TColor color);
        inline TColor getIntensidad();
                void beginDraw();
        void endDraw();
        
    private:
        //TColor intensidad;
};

#endif /* SRC_TLUZ_H_ */