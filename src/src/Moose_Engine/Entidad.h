#ifndef SRC_ENTIDAD_H_
#define SRC_ENTIDAD_H_

class Entidad {
public:
	Entidad() {};
	virtual ~Entidad() {};

	virtual void beginDraw() = 0;
	virtual void endDraw() = 0;
}

#endif /* SRC_ENTIDAD_H_ */
