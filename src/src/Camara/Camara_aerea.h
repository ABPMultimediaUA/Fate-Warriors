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
	
	
	void Camara_Update();
	void update_position();


private:


};



#endif /* SRC_CPP_CAMARA_H_ */


