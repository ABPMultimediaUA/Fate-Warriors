#include "Interfaz_ME.h"
#include "TMooseEngine.h"
#include "TModelado.h"
#include "TTransform.h"
#include "TNodo.h"

Interfaz_ME* Interfaz_ME::_instancia = 0;

Interfaz_ME* Interfaz_ME::get_instancia(){
    if(_instancia == 0){
        _instancia= new Interfaz_ME();
    }
    return _instancia;
}
Interfaz_ME::Interfaz_ME(){

}
Interfaz_ME::~Interfaz_ME(){
    
}
void Interfaz_ME::configuracion_motor(uint16_t x, uint16_t y, bool fullscreen, bool v_sync){
    motor=new TMooseEngine();
}

void Interfaz_ME::crearModelado(char* ruta, float x, float y, float z){
    TModelado* _modelado = motor->crearModelado(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();
    transRotacion->trasladar(x, y, z);
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoTraslacion = motor->crearNodo(nodoRotacion, transTraslacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoTraslacion, transEscalado);
}