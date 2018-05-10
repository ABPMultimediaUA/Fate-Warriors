#include "Opcion_Sonido_Menu.h"

#include "../../Motor_sonido/Interfaz_sonido.h"
#include "../../Interfaz/Motor.h"

Opcion_Sonido_Menu::Opcion_Sonido_Menu(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_Sonido_Menu::~Opcion_Sonido_Menu(){
}

void Opcion_Sonido_Menu::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_sonido_menu(_i_vol);
}

void Opcion_Sonido_Menu::actualiza_valores() {
	_volumen = _motor_sonido->get_volumen_sonido_menu();
}

void Opcion_Sonido_Menu::guarda_volumen() {
	_motor_sonido->guarda_volumen_sonido_menu(_volumen);
	Motor* _motor_interfaz = Motor::Motor_GetInstance();
	_motor_interfaz->set_escala_menu(_volumen);
	_sonido->Play_menu(0);
}