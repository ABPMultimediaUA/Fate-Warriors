
#include "TMooseEngine.h"
#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TTransform.h"
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
    //TNodo* nodoMalla  = motor->crearNodo(nodoTrans2, malla1);
    //TNodo* nodoLuz    = motor->crearNodo(nodoTrans1, luz);
//
    //TNodo* nodoCamara = motor->crearNodo(nodoTrans3, camara);


    return 0;
}