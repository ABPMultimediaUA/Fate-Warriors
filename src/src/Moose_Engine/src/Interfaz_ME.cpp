#include "Interfaz_ME.h"
#include "TMooseEngine.h"
#include "TModelado.h"
#include "TTransform.h"
#include "TNodo.h"
#include "TCamara.h"
#include "TLuz.h"
#include "iNodoModelado.h"
#include "iNodoCamara.h"
#include "iNodoLuz.h"

Interfaz_ME* Interfaz_ME::_instancia = 0;

Interfaz_ME* Interfaz_ME::get_instancia(uint16_t width, uint16_t height){
    if(_instancia == 0){
        _instancia= new Interfaz_ME(width, height);
    }
    return _instancia;
}

Interfaz_ME::Interfaz_ME(uint16_t width, uint16_t height){
    configuracion_motor(width, height, false, false);
}

Interfaz_ME::~Interfaz_ME(){
    
}

void Interfaz_ME::configuracion_motor(uint16_t width, uint16_t height, bool fullscreen, bool v_sync){
    motor = TMooseEngine::get_instancia();
}

iNodoModelado* Interfaz_ME::crearModelado(const char* ruta, float x, float y, float z){
    iNodoModelado* nodo = new iNodoModelado(ruta, x, y, z);
    return nodo;
/*
    TModelado* _modelado = motor->crearModelado(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();
    transRotacion->trasladar(x, y, z);

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoTraslacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoRotacion, transTraslacion);

    TNodo* nodoModelado = motor->crearNodo(nodoEscalado, _modelado);
    */
}

iNodoCamara* Interfaz_ME::crearCamara(bool activa, float x, float y, float z){
    iNodoCamara* nodo = new iNodoCamara(activa, x, y, z);
    return nodo;
}

uint16_t Interfaz_ME::crearLuz(){
    TLuz* luz = motor->crearLuz();
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoTraslacion = motor->crearNodo(nodoRotacion, transTraslacion);

    TNodo* nodoLuz = motor->crearNodoLuz(nodoTraslacion, luz);
}

bool Interfaz_ME::ventana_abierta(){
    return motor->ventana_abierta();
}

void Interfaz_ME::render(){
    motor->draw();
}