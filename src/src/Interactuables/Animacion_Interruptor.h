#ifndef ANIMACION_INTERRUPTOR_H_
#define ANIMACION_INTERRUPTOR_H_

class Motor;
class Interruptor;
class Time;

#include <cstdint>

class Animacion_Interruptor{
public:

	Animacion_Interruptor();
    ~Animacion_Interruptor();  

    void empieza(uint32_t _t_fin, Interruptor* _i_interruptor, short _rotacion_x, short _rotacion_y, short _distancia);
    bool update(double _i_tiempo_desde_ultimo_update);

private:
    Motor* _motor;
    Time* _reloj;

    Interruptor* _interruptor;  // Interruptor asociado a esa animacion
    uint32_t  _t_fin_mirar;     // Tiempo fin de estado mirar a objetivo
    bool _accionado;            // Indica si han sido accionados los interruptores
};

#endif /* ANIMACION_INTERRUPTOR_H_ */