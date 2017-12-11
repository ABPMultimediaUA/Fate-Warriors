#include "Nodo_blackboard.h"

Nodo_blackboard::Nodo_blackboard(int _i_zona_actual){
    _zona_actual=static_cast<Enum_zonas>(_i_zona_actual);
}

Nodo_blackboard::~Nodo_blackboard(){
    _objetos.clear();
}
