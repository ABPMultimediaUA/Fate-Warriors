#ifndef SRC_TENTIDAD_H_
#define SRC_TENTIDAD_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <stack>
class TNodo;
class Shader;

class TEntidad {

public:
	TEntidad();
	virtual ~TEntidad();

	virtual void beginDraw(Shader* _i_shader) = 0;
	virtual void endDraw() = 0;

	void set_mi_nodo(TNodo* nodo);
	TNodo* get_mi_nodo();
	void setID(uint16_t id);
	uint16_t getID();
	glm::mat4 get_matriz();
	

private:
	
protected:
	uint16_t _ID;
	TNodo* _nodo;
    static glm::mat4 _matriz;
    static std::stack<glm::mat4> _pila_matrices;
};

#endif /* SRC_TENTIDAD_H_ */