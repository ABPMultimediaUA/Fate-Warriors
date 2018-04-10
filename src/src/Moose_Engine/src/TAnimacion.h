#ifndef SRC_TANIMACION_H_
#define SRC_TANIMACION_H_
#include "TEntidad.h"
class Shader;
class TRecursoAnimacion;
class Time;
class TAnimacion : public TEntidad{
    public:
        TAnimacion(const char* path);
        ~TAnimacion();
        void beginDraw(Shader* _i_shader) override;
        void draw(Shader* _i_shader);
        void endDraw();
        std::string get_nombre();
        
    private:
        TRecursoAnimacion* _animacion;
        void leerAnimacion(const char* path);
        void update_anim();
        uint8_t _contador_anim;
        double _tiempo_aux;
        Time* _reloj;

};

#endif /* SRC_TANIMACION_H_ */