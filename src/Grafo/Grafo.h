#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
class Arista;

class Vertice
{
  Vertice *sig;
  Arista *ady;
  std::string nombre;
  friend class Grafo;
};

class Arista{
  Arista *sig;
  Vertice *ady;
  int peso;
  friend class Grafo;
};

class Grafo
{
	Vertice *h;
public:
	void Inicializa();
	bool Vacio();
	int Tamano();

	Vertice * GetVertice(std::string nombre);
	void InsertaArista(Vertice *origen, Vertice *destino, int peso);
	void InsertaVertice(std::string nombre);
	void ListaAdyacencia();
	/*void RecorridoAnchura(Vertice *origen);
	void RecorridoProfundidad(Vertice *origen);*/
	void CaminoCortoL2(Vertice *origen, Vertice *destino);
	
};
#endif