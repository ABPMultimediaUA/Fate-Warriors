#include "Enum_zonas.h"
#include "../IA/Enum_Acciones.h"
#include <vector>
#ifndef NODO_BLACKBOARD_H
#define NODO_BLACKBOARD_H

class Objeto;
class Nodo;

class Nodo_blackboard
{

      private:
      Enum_zonas _zona_actual;//
      std::vector<Objeto*> _objetos;
      std::vector<int> _zonas_ady;
      int _ultima_zona;
      unsigned short _lod;
      Enum_Acciones _ultima_accion;
      int _n_zonas;//cantidad de zonas adyacentes(de todos los tipos)


	public:
      Enum_zonas get_zona_actual();
      std::vector<int> get_zonas_ady();
      std::vector<Objeto*> get_objetos();
      int get_ultima_zona();
      unsigned short get_lod();
      Enum_Acciones get_ultima_accion();
      int get_zonas_enemigas();

      void set_lod(int _i_lod);
      void anyadir_zona(int _i_zona);

	  Nodo_blackboard(int _i_zona_actual);
	  ~Nodo_blackboard();
};



#endif