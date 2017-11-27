#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
#include <string>

class Vertice;

class Grafo
{
	Vertice *h;
public:


	Grafo();
	~Grafo();

	bool Vacio();
	int Tamano();

	Vertice * GetVertice(int id);
	void InsertaAristaBi(Vertice *origen, Vertice *destino, int peso);
	void InsertaArista(Vertice *origen, Vertice *destino, int peso);
	void InsertaVertice(int id);
	void ListaAdyacencia();
	/*void RecorridoAnchura(Vertice *origen);
	void RecorridoProfundidad(Vertice *origen);*/
	std::stack<Vertice*> CaminoCortoL2(Vertice *origen, Vertice *destino);

	void EliminarArista(Vertice *origen, Vertice *destino);
	void Anular();
	
};
#endif