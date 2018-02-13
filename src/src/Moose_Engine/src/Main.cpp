
#include "TMooseEngine.h"
#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TMalla.h"
#include "TLuz.h"
#include <iostream>
#include <glm/ext.hpp>
#include <iostream>

int main(){
    //TGestorRecursos* resurseManajer = new TGestorRecursos();
    //resurseManajer->getRecursoMalla("Enemigo.obj");
    TMooseEngine* motor=new TMooseEngine();
	
    TTransform* trans1=motor->crearTransform();
	TTransform* trans2=motor->crearTransform();
	TTransform* trans3=motor->crearTransform();

	TLuz* luz =motor->crearLuz();
    TCamara* camara=motor->crearCamara();
    char cstr[50] = "Enemigo.obj";
    char* cstr2  = cstr;
    TMalla* malla1 = motor->crearMalla(cstr2);

    trans1->escalar(0.5,0.25,0.5);
    trans1->trasladar(0,0,-300);
    trans3->trasladar(10,10,0);


    TNodo* nodoTrans1 = motor->crearNodo(motor->nodoRaiz(),trans1);
    TNodo* nodoTrans2 = motor->crearNodo(motor->nodoRaiz(),trans2);
    TNodo* nodoTrans3 = motor->crearNodo(nodoTrans2, trans3);

    TNodo* nodoMalla  = motor->crearNodo(nodoTrans2, malla1);
    TNodo* nodoLuz    = motor->crearNodo(nodoTrans1, luz);
    TNodo* nodoCamara = motor->crearNodo(nodoTrans3, camara);
    

    glm::mat4 algo=glm::mat4(1.0);
    algo[0]=glm::vec4( 3.0, 4.0, 0.0, 1.0 );
    glm::mat4 algo2=glm::mat4(1.0);
    algo2[1]=glm::vec4( 3.0, 7.0, 0.0, 1.0 );
    glm::mat4 algo3=algo*algo2;//a nivel de papel es algo2 * algo1
    std::cout<<algo3[1][0]<<std::endl;
    /*int nViewport =motor->registrarViewport(x,y,alto,ancho);
    motor->setViewportActivoActivo(nViewport);
    int nCamara=motor->registrarCamara(nodoCamara);
    motor->setCamaraActiva(nCamara);
    int nLuz=motor->registrarLuz(nodoLuz);
    motor->setLuzActiva(nLuz);*/


    return 0;
}