#ifndef TRIGGER_SPACE_H_
#define TRIGGER_SPACE_H_

#include "../Utilidades/Vector.h"
#include "../Tiempo/Time.h"

class TriggerRegion_space{
public:
	
	TriggerRegion_space(Vector2 pos, double radius);
	bool esta_tocando(Vector2 pos, double EntityRadius)const;
	bool esta_activa();
	void activar();
	void desactivar();

protected:
	Vector2 m_vPos; 	//the center of the region	
	double m_dRadius;	//the radius of the region
	bool _active;
	Time* _reloj;
};


#endif /* TRIGGER_SPACE_H_ */