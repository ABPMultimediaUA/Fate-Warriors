#ifndef SRC_ENTIDAD_H_
#define SRC_ENTIDAD_H_

class Entidad {
public:
	Entidad();
	virtual ~Entidad();

	virtual void beginDraw();
	virtual void endDraw();
}

#endif /* SRC_ENTIDAD_H_ */
