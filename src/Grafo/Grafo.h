#ifndef GRAFO_H
#define GRAFO_H

#include <stack>
class Vertice;

class Grafo
{
	Vertice *h;
public:


	Grafo();
	~Grafo();

	bool Vacio();
	int Tamano();

	Vertice * GetVertice(std::string nombre);
	void InsertaArista(Vertice *origen, Vertice *destino, int peso);
	void InsertaVertice(std::string nombre);
	void ListaAdyacencia();
	/*void RecorridoAnchura(Vertice *origen);
	void RecorridoProfundidad(Vertice *origen);*/
	std::stack<Vertice*> CaminoCortoL2(Vertice *origen, Vertice *destino);
	
};
#endif