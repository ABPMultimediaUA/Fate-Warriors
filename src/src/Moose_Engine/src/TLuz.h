#ifndef SRC_TLUZ_H_
#define SRC_TLUZ_H_
#include "TEntidad.h"
class TColor;

class TLuz : public TEntidad{
    public:
        TLuz();
        ~TLuz();
        inline void seIntensidad(TColor color);
        inline TColor getIntensidad();
        void beginDraw(Shader* _i_shader) override;
        void endDraw();
        void setActiva(bool activa);
        
    private:
        bool _activa;
        //TColor intensidad;
};

#endif /* SRC_TLUZ_H_ */