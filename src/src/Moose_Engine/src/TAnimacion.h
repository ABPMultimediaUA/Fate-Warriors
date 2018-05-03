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
        inline void set_bucle(bool _i_bucle){_bucle=_i_bucle;}
        glm::vec3 get_BB();
        
    private:
        TRecursoAnimacion* _animacion;
        bool _bucle;
        void leerAnimacion(const char* path);
        void update_anim();
        uint8_t _contador_anim;
        double _tiempo_aux;
        Time* _reloj;

};

#endif /* SRC_TANIMACION_H_ */