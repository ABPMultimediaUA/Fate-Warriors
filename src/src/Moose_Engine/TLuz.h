#ifndef SRC_TLUZ_H_
#define SRC_TLUZ_H_
#include "TEntidad.h"
class TColor;
class vec3;
class TLuz : public TEntidad{
    public:
        TLuz(glm::vec3 _i_ambiente, glm::vec3 _i_especular, glm::vec3 _i_difusa);
        ~TLuz();
        inline void seIntensidad(TColor color);
        inline TColor getIntensidad();
        void beginDraw(Shader* _i_shader) override;
        void endDraw();
        void setActiva(bool activa);
        inline glm::vec3 get_ambiente(){
            return _ambiente;
        }
        inline glm::vec3 get_especular(){ return _especular;}
        inline glm::vec3 get_difusa(){ return _difusa;}
        
    private:
        bool _activa;
        glm::vec3 _ambiente;
        glm::vec3 _especular;
        glm::vec3 _difusa;

};

#endif /* SRC_TLUZ_H_ */