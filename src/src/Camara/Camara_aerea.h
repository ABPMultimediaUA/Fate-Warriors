#include "../Utilidades/Vector.h"
#include <glm/ext.hpp>
#include "../Interfaz/Motor.h"

#ifndef SRC_CPP_CAMARA_AEREA_H_
#define SRC_CPP_CAMARA_AEREA_H_

class Vector3;

class Input;
class Interpolacion;
class iNodoModelado;
class GLFWwindow;
class iNodoCamara;

class Camara_aerea : public Camara{
public:
	
	Camara_aerea(bool activa);
	~Camara_aerea();
	void Camara_Update() override;
	void update_position() override;


private:


};



#endif /* SRC_CPP_CAMARA_H_ */


