#ifndef PROYECTIL_H_
#define PROYECTIL_H_

#include "../Objeto_Movil.h"
class Proyectil : public Objeto_Movil{
public:
	Proyectil(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter);
	virtual ~Proyectil();

	virtual void 	Update() = 0;
	virtual void 	Render() = 0;

	void	set_direction(float _i_x, float _i_y, float _i_z);
	void 	change_activate_value();

	short 	get_danyo();
	bool 	get_state();
	void 	set_has_impacted();
	bool 	get_has_impacted();
	short	get_id_shooter();

protected:

	short	_id_shooter;
	short	_danyo;
	bool 	_impacted;
	float 	_directionx;
	float 	_directiony;
	float 	_directionz;
	float 	_origenx;
	float	_origeny;
	float	_origenz;
};

#endif /* PROYECTIL_H_ */
