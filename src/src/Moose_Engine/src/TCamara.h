#ifndef SRC_TCAMARA_H_
#define SRC_TCAMARA_H_
#include "TEntidad.h"

class TCamara : public TEntidad{
    public:
        TCamara();
        ~TCamara();
        void setPerspectiva(float x, float y);
        void setParalela(float x, float y);
        glm::mat4 getPerspectiva();
        void beginDraw(Shader* _i_shader) override;
        void endDraw();
        void setActiva(bool activa);
        glm::mat4 calculaView();
    private:
        bool es_perspectiva;
        bool _activa;
        float cercano,lejano;
        
        //posicion y target de la camara para ajustarlos en cada metodo
        glm::vec3 _position;
        glm::vec3 _target;
        glm::mat4 _matriz_view;

};

#endif /* SRC_TCAMARA_H_ */