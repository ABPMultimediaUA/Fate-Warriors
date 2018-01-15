#ifndef SRC_Trampas_H_
#define SRC_Trampas_H_

#include "../Objeto.h"
#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"

class Time;

class Trampas : public Objeto{
public:
	Trampas(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo);
	virtual 	~Trampas();
	
	void update(){};
	virtual void	activar();
	void			desactivar();
	bool			get_estado();
	short			get_danyo();

protected:
	Time *  _reloj;
	Objeto_Motor* _objeto;
	short	_danyo;
	bool	_activa;
};

#endif /* SRC_Trampas_H_ */
