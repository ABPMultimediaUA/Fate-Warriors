#include "iNodoCamara.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TNodo.h"
#include <glm/ext.hpp>

iNodoCamara::iNodoCamara(bool activa){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TCamara* _camara = motor->crearCamara(activa);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoCamara = motor->crearNodoCamara(nodoTraslacion, _camara);
    _nodo_motor = nodoCamara; //almacenamos el puntero al nodo del ME
  
}

iNodoCamara::iNodoCamara(bool activa, float x, float y, float z){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TCamara* _camara = motor->crearCamara(activa);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoCamara = motor->crearNodoCamara(nodoTraslacion, _camara);
    _nodo_motor = nodoCamara; //almacenamos el puntero al nodo del ME
  
}

//implementa de forma manual glm look at insertando en el arbol las rotaciones y traslaciones 
//necesarias para que la camara apunte hacia un punto concreto del espacio 3D
void iNodoCamara::LookAt(Vector3 position, Vector3 target){
    //vectores iniciales de posicion y target
    glm::vec3 _m_position(position._x, position._y, position._z);
    glm::vec3 _m_target  (target._x,   target._y,   target._z)  ;  
    

    //ROTACION ANGULO Z -----> SE APLICA SOBRE EJE X
    //ROTACION ANGULO RIGHT -> SE APLICA SOBRE EJE Y
    //ROTACION ANGULO 
    //vector direction (positive Z)
    glm::vec3 cameraDirection = glm::normalize(_m_position - _m_target);

    //right axis (positive X)
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    //up axis (positive Y)
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    //calculo de angulo entre los ejes y los vectores calculados

    //ejes naturales
    glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
    glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
    // Angulo entre el vector inicial de referencia
	// y el vector de direccion actual 
    float angleX, angleY, angleZ;
    float dot, det;
    
    //dot = inicial.x * _camaraDir.x + inicial.z * _camaraDir.z;
    //det = inicial.x * _camaraDir.z - inicial.z * _camaraDir.x;
    //angle = -(atan2f(_det,_dot)/M_PI)*180;
}