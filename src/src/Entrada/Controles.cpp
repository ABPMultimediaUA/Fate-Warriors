#include "SFML/Graphics.hpp"
#include "Controles.h"
#include "Input.h"

Controles* Controles::instancia=0;

Controles* Controles::Instance(){
	if(instancia==0){
	instancia= new Controles();
	}
	return instancia;
}

Controles::Controles(){
	_firstMouse = true;
}

Controles::~Controles(){}


bool Controles::estaPulsada(Input_key key){
	//W:22  ||A:0  ||D:3  ||S:18  ||esc: 36
	// MouseL: 101 || MouseR: 102

	switch(key){
		case 22: //W
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				return true;
			}
			break;
		
		case 18: //S
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				return true;
			}
			break;

		case 0: //A
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				return true;
			}
			break;
		
		case 3: //D
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				return true;
			}
			break;

		case 36: //ESC
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				return true;
			}
			break;
      
    	case 4: //E
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				return true;
			}
		break;
		
		case 57: //SPACE
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				return true;
			}
			break;

		case 101: //MouseL
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				return true;
			}
			break;

		case 102: //MouseR
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				return true;
			}
			break;

	}
	return false;
}
/*
void Controles::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (_firstMouse)
    {
        _lastX = xpos;
        _lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - _lastX;
    float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top
    _lastX = xpos;
    _lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
*/