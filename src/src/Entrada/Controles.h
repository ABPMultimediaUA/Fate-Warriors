#ifndef SRC_CONTROLES_H_
#define SRC_CONTROLES_H_

#include "Input.h"

class Controles{
public:
	virtual ~Controles();
	bool estaPulsada(Input_key key);
	static Controles* Instance();
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
	static Controles* instancia;

	bool _firstMouse;
	float _lastX;
    float _lastY;

	Controles();
};

#endif /* SRC_CONTROLES_H_ */
