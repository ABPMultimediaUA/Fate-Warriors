#ifndef TRIGGER_SPACE_H_
#define TRIGGER_SPACE_H_

#include "Trigger_region.h"
#include "../Utilidades/Vector.h"


class TriggerRegion_space : public Trigger_region {
public:
	
	TriggerRegion_space(Vector2 pos, double radius);
	bool esta_tocando(Vector2 pos, double EntityRadius)const;
	bool esta_activa();
	void activar();
	void desactivar();

private:
	Vector2 m_vPos; 	//the center of the region	
	double m_dRadius;	//the radius of the region
	bool _active;
};


#endif /* TRIGGER_SPACE_H_ */