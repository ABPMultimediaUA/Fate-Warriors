#ifndef SRC_TANIMACION_H_
#define SRC_TANIMACION_H_

#include "TEntidad.h"

class Shader;
class TRecursoAnimacion;

class TAnimacion : public TEntidad{
    public:
        TAnimacion(const char* path);
        ~TAnimacion();

        void beginDraw(Shader* _i_shader) override;
        void draw(Shader* _i_shader);
        void endDraw();
        std::string get_nombre();
        glm::vec3 get_BB();
        void set_cont_animaciones(uint8_t _i_cont);

        uint8_t get_max_anim();

    private:
        TRecursoAnimacion* _animacion;
        void leerAnimacion(const char* path);

        uint8_t _contador_anim;
    };

#endif /* SRC_TANIMACION_H_ */