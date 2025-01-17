#include "Enum_zonas.h"
#include "../IA/Enum_Acciones.h"
#include <vector>
#include <cstdint>
#ifndef NODO_BLACKBOARD_H
#define NODO_BLACKBOARD_H

class Objeto;
class Nodo;
class NPC;

class Nodo_blackboard
{

      private:	  
      NPC** _NPC;
	uint8_t _maximo_npc;
      Enum_zonas _zona_actual;//
      std::vector<Objeto*> _objetos;
      int* _zonas_ady;
      int _ultima_zona;
      uint8_t _lod;
      Enum_Acciones _ultima_accion;
      int _n_zonas_ady_enemigas;
      int _n_zonas;//cantidad de zonas adyacentes(de todos los tipos)


	public:
      Enum_zonas get_zona_actual();
      inline uint8_t get_maximo_npc(){
            return _maximo_npc;
      }
      inline NPC** get_array_NPC(){
            return _NPC;
      }
      int* get_zonas_ady();
      std::vector<Objeto*> get_objetos();
      int get_ultima_zona();
      inline uint8_t get_lod(){
            return _lod;
      }
      Enum_Acciones get_ultima_accion();
      int get_zonas_enemigas();
      void declarar_zonas_ady(int _i_size);

      void set_lod(int _i_lod);
      void anyadir_zona(int _i_zona);
      void inserta_NPC(NPC* _i_npc);
      void elimina_NPC(NPC* _i_npc);
      NPC* get_NPC(uint8_t num);
	  Nodo_blackboard(int _i_zona_actual, uint8_t _i_n_npc);
	  ~Nodo_blackboard();
};



#endif