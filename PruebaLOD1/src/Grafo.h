#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <string>

class Vertice;
class Arista;
class Grafo
{
protected:
	Vertice *_h;

	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso, int _i_id);
public:


	Grafo();
	~Grafo();

	bool grafo_vacio();
	int grafo_tamano();

	Vertice * grafo_get_vertice(int _i_id);
	Arista * grafo_get_arista(int _i_id);
	void grafo_inserta_arista_bi(Vertice *_i_origen, Vertice *i_i_destino, int _i_peso, int _i_id);	
	void grafo_inserta_vertice(int _i_id,int _i_posx,int _i_posy, Grafo *_i_grafo_lod1);
	void grafo_lista_adyacencia();
	std::stack<Vertice*> grafo_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino);
	void grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino);
	void grafo_anular();
};
#endif