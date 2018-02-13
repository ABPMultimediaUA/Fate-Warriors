#ifndef SRC_TTRANSFORM_H_
#define SRC_TTRANSFORM_H_
#include "TEntidad.h"
//#include "TNodo.h"

class TTransform : public TEntidad{
    public:
        TTransform();
        ~TTransform();

        void identidad();
        void cargar(glm::mat4 matriz);
        void trasponer();
        void trasladar(float _i_x, float _i_y, float _i_z);
        void rotar(float _i_x, float _i_y, float _i_z, float _i_w);
        void escalar(float _i_x, float _i_y, float _i_z);

        void beginDraw();
        void endDraw();
    
    private:
        glm::mat4 _t_matriz;

};

#endif /* SRC_TTRANSFORM_H_ */ //TATE QUIETO
