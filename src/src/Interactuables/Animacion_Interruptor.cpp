#include "Animacion_Interruptor.h"

#include "Interruptor.h"
#include "Puerta_Pincho.h"

#include "../Datos_Partida.h"
#include "../Game.h"

#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"

#include "../Tiempo/Time.h"

Animacion_Interruptor::Animacion_Interruptor(){
   _reloj = Time::Instance();
   _motor = Motor::Motor_GetInstance();

   _accionado = false;
}

Animacion_Interruptor::~Animacion_Interruptor() {

}


void Animacion_Interruptor::empieza(uint32_t _t_fin, Interruptor* _i_interruptor, short _rotacion_x, short _rotacion_y, short _distancia) {
    _t_fin_mirar = _t_fin;

    _interruptor = _i_interruptor;
    
	_motor->poner_camara_a_entidad(_interruptor->get_puerta_asociada()->get_objeto_motor());
	_motor->gira_camara(_interruptor->get_rotacion_x(), _interruptor->get_rotacion_y());
 //   _motor->interpolar_altura(false);

	_motor->update(0);
	_motor->update(0);
}


bool Animacion_Interruptor::update(double _i_tiempo_desde_ultimo_update) {
    //std::cout <<  _t_fin_mirar-_reloj->get_current() << " -- tiempo -- " << std::endl;
    if(_accionado == false && _reloj->get_current() > _t_fin_mirar-2000) {
        _interruptor->accionar();
        _accionado = true;
    }

    if(_reloj->get_current() < _t_fin_mirar) {
		_motor->update(_i_tiempo_desde_ultimo_update);
        return false;
	}
    _accionado = false;
   // _motor->interpolar_altura(true);

    return true;
}