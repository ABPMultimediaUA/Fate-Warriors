#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <string>

class Vertice;
class Arista;
class Nodo_blackboard;
class NPC;
class Grafo
{
private:
	Vertice *_h;

	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino,  int _i_id);
public:


	Grafo();
	~Grafo();

	void Update();
	bool grafo_vacio();
	int grafo_tamano();
	Nodo_blackboard* grafo_get_blackboard(float _i_x, float _i_y);
	Vertice * grafo_get_vertice(int _i_id);
	Vertice * grafo_get_vertice(float _i_x, float _i_y);
	Arista * grafo_get_arista(int _i_id);
	void grafo_crea_arista(int _i_origen,int _i_destino, int _i_id);
	void grafo_inserta_arista_bi(Vertice *_i_origen, Vertice *i_i_destino, int _i_id);	
	void grafo_inserta_vertice(Vertice * _nuevo);
	void grafo_lista_adyacencia();
	std::stack<Vertice*> grafo_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino);
	void grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino);
	
	
	void grafo_set_lod(int _i_id);
	int grafo_get_id_vertice(float _i_x, float _i_y);
	unsigned short grafo_pathfindinglod1(float _i_xorigen, float _i_yorigen, float _i_xdestino, float _i_ydestino);
	void grafo_inserta_NPC(NPC* _i_npc);

private:
	void actualiza_NPC();
	void grafo_anular();
};
#endif