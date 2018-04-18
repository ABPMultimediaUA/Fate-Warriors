#ifndef TRIGGER_SPACE_H_
#define TRIGGER_SPACE_H_

class TriggerRegion_space : public Trigger_region {
public:
	TriggerRegion_space(Vector2 pos, double radius):m_dRadius(radius), m_vPos(pos){}
	bool esta_tocando(Vector2 pos, double EntityRadius)const{
		return Vec2DistanceSq(m_vPos, pos) < (EntityRadius + m_dRadius)*(EntityRadius + m_dRadius);		//distances calculated in squared-distance space
	}

private:
	Vector2 m_vPos; 	//the center of the region	
	double m_dRadius;	//the radius of the region
};


#endif /* TRIGGER_SPACE_H_ */