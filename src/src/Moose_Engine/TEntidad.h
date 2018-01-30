#ifndef SRC_TENTIDAD_H_
#define SRC_TENTIDAD_H_
#include <cstdint>
class TNodo;

class TEntidad {

public:
	TEntidad();
	virtual ~TEntidad();

	virtual void beginDraw() = 0;
	virtual void endDraw() = 0;

	void set_mi_nodo(TNodo* nodo);
	TNodo* get_mi_nodo();
	void setID(uint16_t id);
	uint16_t getID();

private:
	uint16_t _ID;
	TNodo* _nodo;
};

#endif /* SRC_TENTIDAD_H_ */