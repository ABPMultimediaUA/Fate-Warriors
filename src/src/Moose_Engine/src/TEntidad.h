#ifndef SRC_TENTIDAD_H_
#define SRC_TENTIDAD_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <stack>
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
	
protected:
	uint16_t _ID;
	TNodo* _nodo;
    static glm::mat4 matriz;
    static std::stack<glm::mat4> pila_matrices;
};

#endif /* SRC_TENTIDAD_H_ */