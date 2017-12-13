#include "TriggerRegion_space.h"
#include "../Utilidades/Vector.h"
TriggerRegion_space::TriggerRegion_space(Vector2 pos, double radius):m_dRadius(radius), m_vPos(pos), _active(true), _reloj(Time::Instance()){}

bool TriggerRegion_space::esta_tocando(Vector2 pos, double EntityRadius)const{
	return Vector2DistanceSq(m_vPos, pos) < (EntityRadius + m_dRadius)*(EntityRadius + m_dRadius);		//distances calculated in squared-distance space
}


bool TriggerRegion_space::esta_activa(){
	return _active;
}

void TriggerRegion_space::desactivar(){
   	_active=false;
}


void TriggerRegion_space::activar(){
   	_active=true;
}