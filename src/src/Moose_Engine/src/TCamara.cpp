#include "TCamara.h"
#include <iostream>

TCamara::TCamara(){
      
}
TCamara::~TCamara(){}
void TCamara::beginDraw(Shader* _i_shader){

}
void TCamara::endDraw(){
}

void TCamara::setActiva(bool activa){
    _activa = activa;
}

glm::mat4 TCamara::getPerspectiva(){
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 100.0f);
    return projection;
}

//calcula la matriz view de forma directa 
glm::mat4 TCamara::calculaView(){
    //glm::vec3 _m_position(position._x, position._y, position._z);
    //glm::vec3 _m_target  (target._x,   target._y,   target._z)  ;  
    
    //vector direction (positive Z)
    glm::vec3 cameraDirection = glm::normalize(_position - _target);

    //right axis (positive X)
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    //up axis (positive Y)
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 matrixA, matrixB;
    
    //matrixA
    //[columna] [fila]
    matrixA[0][0] = cameraRight.x;
    matrixA[1][0] = cameraRight.y;
    matrixA[2][0] = cameraRight.z;
    matrixA[3][0] = 0;
    
    matrixA[0][1] = up.x;
    matrixA[1][1] = up.y;
    matrixA[2][1] = up.z;
    matrixA[3][1] = 0;
    
    matrixA[0][2] = cameraDirection.x;
    matrixA[1][2] = cameraDirection.y;
    matrixA[2][2] = cameraDirection.z;
    matrixA[3][2] = 0;
    
    matrixA[0][3] = 0;
    matrixA[1][3] = 0;
    matrixA[2][3] = 0;
    matrixA[3][3] = 1;

    //matrixB
    //[columna] [fila]
    matrixB[0][0] = 1;
    matrixB[1][0] = 0;
    matrixB[2][0] = 0;
    matrixB[3][0] = -(_position.x);

    matrixB[0][1] = 0;
    matrixB[1][1] = 1;
    matrixB[2][1] = 0;
    matrixB[3][1] = -(_position.y);
    
    matrixB[0][2] = 0;
    matrixB[1][2] = 0;
    matrixB[2][2] = 1;
    matrixB[3][2] = -(_position.z);
    
    matrixB[0][3] = 0;
    matrixB[1][3] = 0;
    matrixB[2][3] = 0;
    matrixB[3][3] = 1;

    _matriz_view = matrixA * matrixB;
    return _matriz_view;
}

void TCamara::setVecPosition(glm::vec3 position){
    _position = position;
}

void TCamara::setVecTarget(glm::vec3 target){
    _target = target;
}