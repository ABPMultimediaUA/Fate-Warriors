#include "Enum_zona.h"
#include "../IA/Enum_Acciones.h"
#include <vector>
#ifndef NODO_BLACKBOARD_H
#define NODO_BLACKBOARD_H

class Objeto;
class Nodo;

class Nodo_blackboard
{
	public:
      Enum_zonas _zona_actual;
      std::vector<Objeto*> _objetos;
      std::vector<Nodo*> _zonas_ady;
      Nodo* _ultima_zona;
      unsigned short _lod;
      Enum_Acciones _ultima_accion;
      int _n_zonas;



	  Nodo_blackboard(int _i_zona_actual);
	  ~Nodo_blackboard();
     Enum_zonas get_ady(int _i_id);
     Nodo* get_ultima_zona();
};



#endif