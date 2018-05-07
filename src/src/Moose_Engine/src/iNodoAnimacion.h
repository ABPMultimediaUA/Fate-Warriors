#ifndef SRC_INODOANIMACION_H_
#define SRC_INODOANIMACION_H_

#include "../../Utilidades/Vector.h"
#include "iNodoModelado.h"

class TAnimacion;
class Time;

class iNodoAnimacion : public iNodoModelado{
    public:
        iNodoAnimacion(bool bucle, const char* ruta, uint8_t _num_ruta);
        iNodoAnimacion(bool bucle, const char* ruta, float x, float y, float z, uint8_t _num_ruta);
        ~iNodoAnimacion();

        void cambiar_modelado(const char * _i_ruta, uint8_t _num_ruta) override;
        void update_anim() override;
        Vector3 getBB() override;
        
    private:
        uint8_t _ruta_actual;

        bool _bucle;
        bool _fin_animacion;
        
        uint8_t _contador_anim;
        uint8_t _max_anim;

        Time* _reloj;
        double _tiempo_aux;

        TAnimacion* _animacion;

        const char* _ruta_idle;
};

#endif